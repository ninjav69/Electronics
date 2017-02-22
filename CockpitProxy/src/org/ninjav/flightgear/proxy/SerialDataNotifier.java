/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.ninjav.flightgear.proxy;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author root
 */
public class SerialDataNotifier {
    private List<SerialDataListener> listeners = new ArrayList<SerialDataListener>();

    public void addSerialDataListener(SerialDataListener l) {
        listeners.add(l);
    }

    public void removeSerialDataListener(SerialDataListener l) {
        listeners.remove(l);
    }

    public void notifySerialDataListeners(byte[] data) {
        for (SerialDataListener l : listeners) {
            l.onSerialData(data);
        }
    }
}
