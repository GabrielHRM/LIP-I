package game.inputs;
import game.enums.CommandsEnum;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import javax.swing.*;
import java.awt.*;
public class ButtonInputs implements IInputs {
    private final BlockingQueue<CommandsEnum> queue = new LinkedBlockingQueue<>();
    private final JFrame frame;
    public ButtonInputs() {
        frame = new JFrame("Buttons Input");
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setLayout(new GridLayout(3, 3));
        JButton up = new JButton("UP"); up.addActionListener(e -> queue.offer(CommandsEnum.UP));
        JButton down = new JButton("DOWN"); down.addActionListener(e -> queue.offer(CommandsEnum.DOWN));
        JButton left = new JButton("LEFT"); left.addActionListener(e -> queue.offer(CommandsEnum.LEFT));
        JButton right = new JButton("RIGHT"); right.addActionListener(e -> queue.offer(CommandsEnum.RIGHT));
        JButton exit = new JButton("EXIT"); exit.addActionListener(e -> queue.offer(CommandsEnum.EXIT));
        frame.add(new JLabel()); frame.add(up); frame.add(new JLabel());
        frame.add(left); frame.add(exit); frame.add(right);
        frame.add(new JLabel()); frame.add(down); frame.add(new JLabel());
        frame.pack();
        frame.setVisible(true);
    }
    @Override
    public CommandsEnum waitCommand() {
        try { return queue.take(); } catch (InterruptedException e) { return CommandsEnum.EXIT; }
    }
    @Override
    public String getDeviceName() { return "Buttons"; }
}
