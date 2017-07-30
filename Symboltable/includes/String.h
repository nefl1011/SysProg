#ifndef STRING_H_
#define STRING_H_

class String {
public:
    /*
     * Gibt die Länge eines Wortes zurück
     */
    static int length(const char *lexem);

    /*
     * Vergleiche Lexem mit gespeicherten
     * Wort im Element
     */
    static bool compare(const char *lexem1, const char *lexem2);

    /*
     * Returns a string, which is all uppercase.
     */
    static char *toUpper(const char *source);


    static char *strdup(const char *source);


    static char *strcpy(char *destination, const char *source);
};


#endif // STRING_H
