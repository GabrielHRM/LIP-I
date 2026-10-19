package game.lang;

import java.util.Locale;

public enum LanguageEnum {
    ENGLISH,
    PORTUGUESE,
    SPANISH;

    public static LanguageEnum from() {
        return ENGLISH;
    }

    public static LanguageEnum from(String lang) {
        try {
            return valueOf(lang.trim().toUpperCase(Locale.ROOT));
        } catch (IllegalArgumentException e) {
            throw new IllegalArgumentException(
                "Language must be english, portuguese, or spanish: " + lang,
                e
            );
        }
    }
}
