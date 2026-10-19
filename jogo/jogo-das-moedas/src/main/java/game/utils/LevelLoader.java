package game.utils;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import game.world.Grid;
public class LevelLoader {
    public List<Grid> loadAll(Path file) throws IOException {
        List<List<String>> levels = new ArrayList<>();
        List<String> currentLevel = new ArrayList<>();
        for (String line : Files.readAllLines(file)) {
            if (line.equals("---")) {
                if (currentLevel.isEmpty()) throw new IllegalArgumentException("Empty level.");
                levels.add(currentLevel);
                currentLevel = new ArrayList<>();
            } else if (!line.isBlank()) {
                currentLevel.add(line);
            }
        }
        if (!currentLevel.isEmpty()) levels.add(currentLevel);
        List<Grid> loadedLevels = new ArrayList<>();
        for (int index = 0; index < levels.size(); index++)
            loadedLevels.add(parseLevel(levels.get(index), index + 1));
        return loadedLevels;
    }
    public Grid load(Path file, int levelNumber) throws IOException {
        List<Grid> levels = loadAll(file);
        if (levelNumber < 1 || levelNumber > levels.size())
            throw new IllegalArgumentException("Level must be between 1 and " + levels.size() + ".");
        return levels.get(levelNumber - 1);
    }
    private Grid parseLevel(List<String> rows, int levelNumber) {
        int width = rows.get(0).length();
        String[] mapRows = new String[rows.size()];
        int playerX = -1, playerY = -1;
        List<int[]> coins = new ArrayList<>();
        for (int y = 0; y < rows.size(); y++) {
            StringBuilder mapRow = new StringBuilder(width);
            for (int x = 0; x < width; x++) {
                char cell = rows.get(y).charAt(x);
                switch (cell) {
                    case '@' -> { playerX = x; playerY = y; mapRow.append(' '); }
                    case '$' -> { coins.add(new int[] { x, y }); mapRow.append(' '); }
                    case '#', '.' -> mapRow.append(cell == '#' ? '#' : ' ');
                    default -> throw new IllegalArgumentException("Invalid char: " + cell);
                }
            }
            mapRows[y] = mapRow.toString();
        }
        return new Grid(mapRows, playerX, playerY, coins);
    }
}
