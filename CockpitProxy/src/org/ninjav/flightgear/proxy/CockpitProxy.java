/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.ninjav.flightgear.proxy;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.UnsupportedCommOperationException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.LinkedList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * This class is the intermediate for the comms between the serial port
 * and the socket to flightgear. Data read from the serial port is interpreted
 * and written to the flightgear socket, and data form the flightgear socket
 * is interpreted and written to the serial port.
 *
 * @author root
 */
public class CockpitProxy implements SocketDataListener, SerialDataListener {

    private int socketPort;
    private String serialPort;
    private SocketReader socketReader;
    private SocketWriter socketWriter;
    private SerialReader serialReader;
    private SerialWriter serialWriter;

    public CockpitProxy(int socketPort, String serialPort) {
        this.socketPort = socketPort;
        this.serialPort = serialPort;
    }

    public void openSocket() {
        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(socketPort);
        } catch (IOException e) {
            System.err.println("Could not listen on port: " + socketPort);
            System.exit(1);
        }

        Socket clientSocket = null;
        try {
            clientSocket = serverSocket.accept();
            clientSocket.setKeepAlive(true);
        } catch (IOException e) {

            System.err.println("Accept failed.");
            System.exit(1);
        }

        InputStream in = null;
        try {
            in = clientSocket.getInputStream();
        } catch (IOException ex) {
            System.err.println("Could not get client input stream");
            System.exit(1);
        }
        OutputStream out = null;
        try {
            out = clientSocket.getOutputStream();
        } catch (IOException ex) {
            System.err.println("Could not get client output stream");
            System.exit(1);
        }

        socketReader = new SocketReader(in);
        socketReader.addSocketDataListener(this);
        new Thread(socketReader).start();
        socketWriter = new SocketWriter(out);
        new Thread(socketWriter).start();
    }

    public void openSerial() {
        CommPortIdentifier portIdentifier = null;
        try {
            portIdentifier = CommPortIdentifier.getPortIdentifier(serialPort);
        } catch (NoSuchPortException ex) {
            Logger.getLogger(CockpitProxy.class.getName()).log(Level.SEVERE, null, ex);
            System.exit(1);
        }
        if (portIdentifier.isCurrentlyOwned()) {
            System.out.println("Error: Port is currently in use");
        } else {
            CommPort commPort = null;
            try {
                commPort = portIdentifier.open(this.getClass().getName(), 2000);
            } catch (PortInUseException ex) {
                Logger.getLogger(CockpitProxy.class.getName()).log(Level.SEVERE, null, ex);
                System.exit(1);
            }

            if (commPort instanceof SerialPort) {
                SerialPort port = (SerialPort) commPort;
                try {
                    port.setSerialPortParams(9600, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
                } catch (UnsupportedCommOperationException ex) {
                    Logger.getLogger(CockpitProxy.class.getName()).log(Level.SEVERE, null, ex);
                    System.exit(1);
                }

                InputStream in = null;
                try {
                    in = port.getInputStream();
                } catch (IOException ex) {
                    Logger.getLogger(CockpitProxy.class.getName()).log(Level.SEVERE, null, ex);
                }
                OutputStream out = null;
                try {
                    out = port.getOutputStream();
                } catch (IOException ex) {
                    Logger.getLogger(CockpitProxy.class.getName()).log(Level.SEVERE, null, ex);
                }

                serialReader = new SerialReader(in);
                serialReader.addSerialDataListener(this);
                serialWriter = new SerialWriter(out);
                new Thread(serialReader).start();
                new Thread(serialWriter).start();

            } else {
                System.out.println("Error: Only serial ports are handled by this example.");
            }
        }
    }

    public void run() {
        openSocket();
        openSerial();
    }

    public void onSocketData(byte[] data) {
        // Interpret data from flightgear and write
        // data to serial port.
        System.out.println("Socket Data[" + new String(data) + "]");
    }

    public void onSerialData(byte[] data) {
        // Interpret data from the serial port and
        // write data to flightgear socket.
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < data.length; i++) {
            String hex = String.format("%02x", data[i]);
            sb.append(hex);
        }
        
        System.out.println("Serial Data[" + sb.toString() + "]");
    }

    public class SocketReader extends SocketDataNotifier implements Runnable {

        private InputStream is;

        public SocketReader(InputStream is) {
            this.is = is;
        }

        public void run() {
            byte[] buffer = new byte[1024];
            int len = -1;
            try {
                while ((len = this.is.read(buffer)) > -1) {
                    System.out.print(new String(buffer, 0, len));
                    byte[] data = new byte[len];
                    for (int i = 0; i < len; i++) {
                        data[i] = buffer[i];
                    }
                    notifySocketListeners(data);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public class SocketWriter implements Runnable {

        private OutputStream os;
        private final List queue = new LinkedList();

        public void process(byte[] data) {
            synchronized (queue) {
                queue.add(data);
                queue.notify();
            }
        }

        public SocketWriter(OutputStream os) {
            this.os = os;
        }

        public void run() {

            while (true) {
                try {
                    // Wait for data to become available
                    synchronized (queue) {
                        while (queue.isEmpty()) {
                            try {
                                queue.wait();
                            } catch (InterruptedException e) {
                                /* just ignore it */
                            }
                        }
                        byte[] data = (byte[]) queue.remove(0);
                        this.os.write(data);
                    }

                } catch (IOException e) {
                    e.printStackTrace();
                } catch (Throwable e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public class SerialReader extends SerialDataNotifier implements Runnable {

        private InputStream is;

        public SerialReader(InputStream is) {
            this.is = is;
        }

        public void run() {
            byte[] buffer = new byte[1024];
            int len = -1;
            try {
                while ((len = this.is.read(buffer)) > -1) {
                    System.out.print(new String(buffer, 0, len));
                    byte[] data = new byte[len];
                    for (int i = 0; i < len; i++) {
                        data[i] = buffer[i];
                    }
                    notifySerialDataListeners(data);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public class SerialWriter implements Runnable {

        private OutputStream os;
        private final List queue = new LinkedList();

        public void process(byte[] data) {
            synchronized (queue) {
                queue.add(data);
                queue.notify();
            }
        }

        public SerialWriter(OutputStream os) {
            this.os = os;
        }

        public void run() {
            while (true) {
                try {
                    // Wait for data to become available
                    synchronized (queue) {
                        while (queue.isEmpty()) {
                            try {
                                queue.wait();
                            } catch (InterruptedException e) {
                                /* just ignore it */
                            }
                        }
                        byte[] data = (byte[]) queue.remove(0);
                        this.os.write(data);
                    }

                } catch (IOException e) {
                    e.printStackTrace();
                } catch (Throwable e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
