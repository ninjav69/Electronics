/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.ninjav.flightgear.proxy;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author apickard
 */
public class SocketDataNotifier {

    private List<SocketDataListener> listeners = new ArrayList<SocketDataListener>();
    
    public void addSocketDataListener(SocketDataListener l) {
        listeners.add(l);
    }
    
    public void removeSocketDataListener(SocketDataListener l) {
        listeners.remove(l);
    }
    
    public void notifySocketListeners(byte[] data) {
        for (SocketDataListener l : listeners) {
            l.onSocketData(data);
        }
    }
}
