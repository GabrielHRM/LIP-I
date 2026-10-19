package game;

import java.io.IOException;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

import game.enums.InputsEnum;
import game.enums.RendererEnum;
import game.enums.LanguageEnum;
import game.inputs.IInputs;
import game.inputs.InputsFactory;
import game.language.ILanguage;
import game.language.LanguageFactory;
import game.ui.IRenderer;
import game.ui.RendererFactory;
import game.utils.LevelLoader;
import game.world.Grid;
import game.world.Progress;
import game.world.gobjects.Coin;
import game.world.gobjects.Player;

public class MainGame {

    public static void main(String[] args) throws IOException {
        LaunchOptions options = loadInput(args);

        List<Grid> grids = new LevelLoader().loadAll(Path.of("levels.txt"));

        if (options.levelNumber() < 1 || options.levelNumber() > grids.size())
            throw new IllegalArgumentException(
                "Level must be between 1 and " + grids.size() + ".");

        IInputs input = new InputsFactory().create(options.inputMode());
        IRenderer renderer = new RendererFactory().create(options.rendererMode());
        ILanguage language = new LanguageFactory().create(options.langMode());

        Progress progress = new Progress();

        for (int index = options.levelNumber() - 1; index < grids.size(); index++) {
            Grid grid = grids.get(index);
            Player player = new Player(grid.getPlayerX(), grid.getPlayerY());

            List<Coin> coins = new ArrayList<>();
            for (int[] position : grid.getCoinPositions())
                coins.add(new Coin(position[0], position[1], 10));

            Level level = new Level(grid, player, progress, coins, input, renderer, language);
            if (!level.run()) {
                language.printEarlyExit(renderer, progress.getScore());
                return;
            }
        }
        language.printGameOver(renderer, progress.getScore());
    }

    private static LaunchOptions loadInput(String[] args) {
        InputsEnum inputMode = null;
        RendererEnum rendererMode = null;
        LanguageEnum langMode = null;
        int levelNumber = 1;

        for (int index = 0; index < args.length; index++) {
            switch (args[index]) {
                case "-i" -> {
                    if (++index >= args.length)
                        throw new IllegalArgumentException("Missing value for -i.");
                    inputMode = InputsEnum.from(args[index]);
                }
                case "-r" -> {
                    if (++index >= args.length)
                        throw new IllegalArgumentException("Missing value for -r.");
                    rendererMode = RendererEnum.from(args[index]);
                }
                case "-l" -> {
                    if (++index >= args.length)
                        throw new IllegalArgumentException("Missing value for -l.");
                    levelNumber = Integer.parseInt(args[index]);
                }
                case "-lang" -> {
                    if (++index >= args.length)
                        throw new IllegalArgumentException("Missing value for -lang.");
                    langMode = LanguageEnum.from(args[index]);
                }
                default -> throw new IllegalArgumentException(
                    "Unknown option: " + args[index] + ". Use -i, -r, -l, or -lang.");
            }
        }

        return new LaunchOptions(
            inputMode == null ? InputsEnum.from() : inputMode,
            rendererMode == null ? RendererEnum.from() : rendererMode,
            langMode == null ? LanguageEnum.from() : langMode, 
            levelNumber
        );
    }

    private record LaunchOptions(
        InputsEnum inputMode,
        RendererEnum rendererMode,
        LanguageEnum langMode,
        int levelNumber
    ) {}
}