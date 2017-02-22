/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package cockpitproxy;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.UnsupportedCommOperationException;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Enumeration;

/**
 *
 * @author root
 */
public class SerialLcd {

    public static final int LCD_CLEAR = 0x01;
    public static final int LCD_GOTO = 0x80;
    private Enumeration portList;
    private CommPortIdentifier portId;
    private String displayLine1 = "";
    private String displayLine2 = "";
    private SerialPort serialPort;
    private OutputStream outputStream;

    public void open(String port) throws SerialLcdException {
        portList = CommPortIdentifier.getPortIdentifiers();

        portId = (CommPortIdentifier) portList.nextElement();

        if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {

            if (portId.getName().equals(port)) {
                try {
                    serialPort =
                            (SerialPort) portId.open("SerialLcd", 2000);
                } catch (PortInUseException e) {
                    throw new SerialLcdException(e.getMessage());
                }

                try {
                    outputStream = serialPort.getOutputStream();
                } catch (IOException e) {
                    throw new SerialLcdException(e.getMessage());
                }

                try {
                    serialPort.setSerialPortParams(9600,
                            SerialPort.DATABITS_8,
                            SerialPort.STOPBITS_1,
                            SerialPort.PARITY_NONE);
                } catch (UnsupportedCommOperationException e) {
                    throw new SerialLcdException(e.getMessage());
                }

                try {
                    serialPort.notifyOnOutputEmpty(true);
                } catch (Exception e) {
                    throw new SerialLcdException(e.getMessage());
                }
            }
        }
    }

    public void close() {
        serialPort.close();
    }

    public String getDisplayLine1() {
        return displayLine1;
    }

    public void setDisplayLine1(String displayLine1) {
        this.displayLine1 = displayLine1;
    }

    public String getDisplayLine2() {
        return displayLine2;
    }

    public void setDisplayLine2(String displayLine2) {
        this.displayLine2 = displayLine2;
    }

    public void update() throws SerialLcdException {
        try {
            outputStream.write(SerialLcd.LCD_CLEAR);
            outputStream.write(displayLine1.getBytes());
            outputStream.write(SerialLcd.LCD_GOTO | 0x40);
            outputStream.write(displayLine2.getBytes());
        } catch (IOException e) {
            throw new SerialLcdException(e.getMessage());
        }
    }
}
