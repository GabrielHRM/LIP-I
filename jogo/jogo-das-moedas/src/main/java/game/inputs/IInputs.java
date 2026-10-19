package game.inputs;
import game.enums.CommandsEnum;
public interface IInputs {
    CommandsEnum waitCommand();
    String getDeviceName();
}
