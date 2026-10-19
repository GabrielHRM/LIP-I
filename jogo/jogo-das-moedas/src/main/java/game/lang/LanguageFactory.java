package game.lang;
import game.ui.IRenderer;
import game.utils.IFactory;
public class LanguageFactory implements IFactory<Language, LanguageEnum> {
    private final IRenderer renderer;
    public LanguageFactory(IRenderer renderer) { this.renderer = renderer; }
    @Override
    public Language create(LanguageEnum key) {
        return switch (key) {
            case ENGLISH -> new English(renderer);
            case PORTUGUESE -> new Portuguese(renderer);
            case SPANISH -> new Spanish(renderer);
        };
    }
}
