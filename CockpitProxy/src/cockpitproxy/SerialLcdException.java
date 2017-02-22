/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package cockpitproxy;

/**
 *
 * @author root
 */
public class SerialLcdException extends Exception {

    /**
     * Creates a new instance of <code>SerialLcdException</code> without detail message.
     */
    public SerialLcdException() {
    }


    /**
     * Constructs an instance of <code>SerialLcdException</code> with the specified detail message.
     * @param msg the detail message.
     */
    public SerialLcdException(String msg) {
        super(msg);
    }
}
