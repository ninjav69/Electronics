/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package cockpitproxy;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author root
 */
public class RotarySensor implements Runnable {

    private float freq = 118.25f;

    public void run() {
        try {
            Process proc = new ProcessBuilder("/usr/local/bin/rotary").start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getInputStream()));
            while (true) {
                String line = reader.readLine();
                if (line == null) {
                    break;
                }
                if (line.trim().equals("CW")) {
                    freq += 0.025f;
                } else {
                    freq -= 0.025f;
                }
                System.out.format("%03.3f\n", freq);
            }
        } catch (IOException ex) {
            Logger.getLogger(RotarySensor.class.getName()).log(Level.SEVERE, null, ex);
            System.exit(1);
        }

    }

}
