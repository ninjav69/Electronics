/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package cockpitproxy;

import org.ninjav.flightgear.proxy.CockpitProxy;

/**
 *
 * @author root
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        new CockpitProxy(8000, "/dev/ttyUSB0").run();
    }
}
