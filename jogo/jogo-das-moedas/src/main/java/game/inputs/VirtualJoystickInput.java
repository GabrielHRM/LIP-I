package game.inputs;

import game.enums.CommandsEnum;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class VirtualJoystickInput implements IInputs {

    private final BlockingQueue<CommandsEnum> queue = new LinkedBlockingQueue<>();
    private final JFrame frame;

    public VirtualJoystickInput() {
        frame = new JFrame("Virtual Joystick");
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        
        JPanel panel = new JPanel();
        panel.add(new JLabel("Click to move (Top=UP, Bottom=DOWN, Left=LEFT, Right=RIGHT)"));
        panel.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                int w = panel.getWidth();
                int h = panel.getHeight();
                int x = e.getX();
                int y = e.getY();
                
                if (y < h / 3) {
                    queue.offer(CommandsEnum.UP);
                } else if (y > 2 * h / 3) {
                    queue.offer(CommandsEnum.DOWN);
                } else if (x < w / 3) {
                    queue.offer(CommandsEnum.LEFT);
                } else if (x > 2 * w / 3) {
                    queue.offer(CommandsEnum.RIGHT);
                } else {
                    queue.offer(CommandsEnum.NONE);
                }
            }
        });
        
        frame.add(panel);
        frame.setSize(400, 400);
        frame.setVisible(true);
    }

    @Override
    public CommandsEnum waitCommand() {
        try { 
            return queue.take(); 
        } catch (InterruptedException e) { 
            return CommandsEnum.EXIT; 
        }
    }

    @Override
    public String getDeviceName() {
        return "Virtual Joystick";
    }
}
