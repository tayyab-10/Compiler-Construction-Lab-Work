#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

// --- Token Types Definition ---
// Using an enum for clarity and mapping to specific token categories.
enum TokenType {
    // End of File marker
    END_OF_FILE,

    // Keywords [cite: 134-137]
    KEYWORD_PROGRAM, KEYWORD_CLASS, KEYWORD_IF, KEYWORD_ELSE, KEYWORD_WHILE,
    KEYWORD_READ, KEYWORD_FINAL, KEYWORD_NEW, KEYWORD_VOID, KEYWORD_PRINT,
    KEYWORD_RETURN,

    // Identifiers and Constants [cite: 128-132]
    IDENTIFIER,
    NUMBER_CONST,
    CHAR_CONST,

    // Operators and Separators [cite: 138-149, 254-256]
    OP_PLUS, OP_MINUS, OP_MUL, OP_DIV, OP_MOD, // Arithmetic
    OP_ASSIGN, // =
    OP_EQUAL, OP_NOT_EQUAL, OP_GT, OP_GE, OP_LT, OP_LE, // Relational
    
    SEP_LPAREN, SEP_RPAREN, SEP_LBRACE, SEP_RBRACE, SEP_LBRACKET, SEP_RBRACKET, // Parentheses/Braces
    SEP_SEMICOLON, SEP_COMMA, SEP_DOT, // Punctuation

    // Error or Unknown
    TOKEN_ERROR
};

// --- Token Structure ---
// Represents a recognized token.
struct Token {
    TokenType type;
    string lexeme;
    int line;
};

// Map to convert TokenType enum back to a readable string for output file.
map<TokenType, string> tokenTypeNames = {
    {END_OF_FILE, "END_OF_FILE"},
    {KEYWORD_PROGRAM, "KEYWORD_PROGRAM"}, {KEYWORD_CLASS, "KEYWORD_CLASS"}, {KEYWORD_IF, "KEYWORD_IF"},
    {KEYWORD_ELSE, "KEYWORD_ELSE"}, {KEYWORD_WHILE, "KEYWORD_WHILE"}, {KEYWORD_READ, "KEYWORD_READ"},
    {KEYWORD_FINAL, "KEYWORD_FINAL"}, {KEYWORD_NEW, "KEYWORD_NEW"}, {KEYWORD_VOID, "KEYWORD_VOID"},
    {KEYWORD_PRINT, "KEYWORD_PRINT"}, {KEYWORD_RETURN, "KEYWORD_RETURN"},
    {IDENTIFIER, "IDENTIFIER"},
    {NUMBER_CONST, "NUMBER_CONST"},
    {CHAR_CONST, "CHAR_CONST"},
    {OP_PLUS, "OP_PLUS"}, {OP_MINUS, "OP_MINUS"}, {OP_MUL, "OP_MUL"}, {OP_DIV, "OP_DIV"}, 
    {OP_MOD, "OP_MOD"}, {OP_ASSIGN, "OP_ASSIGN"},
    {OP_EQUAL, "OP_EQUAL"}, {OP_NOT_EQUAL, "OP_NOT_EQUAL"}, {OP_GT, "OP_GT"}, {OP_GE, "OP_GE"},
    {OP_LT, "OP_LT"}, {OP_LE, "OP_LE"},
    {SEP_LPAREN, "SEP_LPAREN"}, {SEP_RPAREN, "SEP_RPAREN"}, {SEP_LBRACE, "SEP_LBRACE"}, 
    {SEP_RBRACE, "SEP_RBRACE"}, {SEP_LBRACKET, "SEP_LBRACKET"}, {SEP_RBRACKET, "SEP_RBRACKET"}, 
    {SEP_SEMICOLON, "SEP_SEMICOLON"}, {SEP_COMMA, "SEP_COMMA"}, {SEP_DOT, "SEP_DOT"},
    {TOKEN_ERROR, "TOKEN_ERROR"}
};

// Map for quick keyword lookup
map<string, TokenType> keywords = {
    {"program", KEYWORD_PROGRAM}, {"class", KEYWORD_CLASS}, {"if", KEYWORD_IF}, 
    {"else", KEYWORD_ELSE}, {"while", KEYWORD_WHILE}, {"read", KEYWORD_READ},
    {"final", KEYWORD_FINAL}, {"new", KEYWORD_NEW}, {"void", KEYWORD_VOID}, 
    {"print", KEYWORD_PRINT}, {"return", KEYWORD_RETURN}
};

// --- Global State and File Streams ---
ifstream inputFile;
ofstream outputFile;
int currentLine = 1;

void outputToken(const Token& token) {
    // Writing the token stream in a clean format.
    outputFile << "Line " << token.line << ": (" << tokenTypeNames[token.type] << ", \"" << token.lexeme << "\")" << endl;
}

// --- CORE LEXICAL ANALYZER FUNCTION (State-Based Approach) ---

Token getNextToken() {
    char ch;
    string lexeme = "";

    // The main loop is the START state of the DFA (State 0).
    while (inputFile.get(ch)) {
        // --- 1. HANDLE WHITESPACE and COMMENTS [cite: 125, 126, 151] ---
        // Whitespace handling (State 0 -> State 0)
        if (isspace(ch)) {
            if (ch == '\n') {   // increment es liye kr rhy hn kyn ky hamara lookahead sae line ki position pr ho 
                currentLine++; // Track line numbers for error reporting.
            }
            continue; // Ignore whitespace and loop back to START state.
        }

        // 2. START OF IDENTIFIER or KEYWORD (State 1) 
        if (isalpha(ch)) {
            lexeme += ch;
            // Loop until a non-letter/non-digit is encountered
            while (inputFile.get(ch) && (isalnum(ch) || ch == '_')) {   // we are building the lexeme here isalnum is used to check if the character is alphanumeric it contains digits and letters
                lexeme += ch;
            }
            // Put the look-ahead character back (unget)
            inputFile.unget();

            // Check if the recognized lexeme is a keyword or an identifier[cite: 129, 130].
            if (keywords.count(lexeme)) {  // map ma agr lexeme exist krta hua toh retrun kr dyn gn 
                return {keywords[lexeme], lexeme, currentLine};
            } else {
                return {IDENTIFIER, lexeme, currentLine};
            }
        }

        // --- 3. START OF NUMBER CONSTANT (State 2) [cite: 124, 125, 131, 132] ---
        if (isdigit(ch)) {
            lexeme += ch;
            // Loop until a non-digit is encountered
            while (inputFile.get(ch) && isdigit(ch)) {
                lexeme += ch;
            }
            inputFile.unget(); // Put the look-ahead character back
            return {NUMBER_CONST, lexeme, currentLine};
        }

        // --- 4. START OF CHARACTER CONSTANT (State 3-4) [cite: 31, 132] ---
        if (ch == '\'') { // Start Quote      es block ma hm char constant ko handle kr rhy hn jesy ky 'a' ya '1'
            if (inputFile.get(ch) && ch != '\n') {
                lexeme += ch; // The character itself
                if (inputFile.get(ch) && ch == '\'') { // End Quote
                    return {CHAR_CONST, "'" + lexeme + "'", currentLine};
                }
            }
            // Error handling for malformed char constant
            return {TOKEN_ERROR, "Malformed char constant", currentLine};
        }

        // --- 5. START OF OPERATORS / COMMENTS (State 5-9) ---
        // The most complex section involving multi-character tokens
        switch (ch) {
            case '+': return {OP_PLUS, "+", currentLine};
            case '-': return {OP_MINUS, "-", currentLine};
            case '*': return {OP_MUL, "*", currentLine};
            case '%': return {OP_MOD, "%", currentLine};
            
            case '(': return {SEP_LPAREN, "(", currentLine};
            case ')': return {SEP_RPAREN, ")", currentLine};
            case '{': return {SEP_LBRACE, "{", currentLine};
            case '}': return {SEP_RBRACE, "}", currentLine};
            case '[': return {SEP_LBRACKET, "[", currentLine};
            case ']': return {SEP_RBRACKET, "]", currentLine};
            case ';': return {SEP_SEMICOLON, ";", currentLine};
            case ',': return {SEP_COMMA, ",", currentLine};
            case '.': return {SEP_DOT, ".", currentLine};
            
            case '=':
                // Check for '==' (Relational Equal) [cite: 140]
                if (inputFile.get(ch) && ch == '=') {
                    return {OP_EQUAL, "==", currentLine};
                }
                inputFile.unget(); // Otherwise, it's a single '=' (Assignment)[cite: 147].
                return {OP_ASSIGN, "=", currentLine};
            
            case '!':
                // Check for '!=' (Not Equal) [cite: 141]
                if (inputFile.get(ch) && ch == '=') {
                    return {OP_NOT_EQUAL, "!=", currentLine};
                }
                // Error: '!' alone is not a valid token in MicroJava.
                return {TOKEN_ERROR, "Invalid token !", currentLine};

            case '>':
                // Check for '>=' (Greater or Equal) [cite: 143]
                if (inputFile.get(ch) && ch == '=') {
                    return {OP_GE, ">=", currentLine};
                }
                inputFile.unget(); // Otherwise, it's a single '>' (Greater Than).
                return {OP_GT, ">", currentLine};

            case '<':
                // Check for '<=' (Less or Equal) [cite: 146]
                if (inputFile.get(ch) && ch == '=') {
                    return {OP_LE, "<=", currentLine};
                }
                inputFile.unget(); // Otherwise, it's a single '<' (Less Than)[cite: 145].
                return {OP_LT, "<", currentLine};
                
            case '/':
                // Check for '//' (Comment) [cite: 151]
                if (inputFile.get(ch) && ch == '/') {
                    // Skip all characters until the end of the line ('\n') or EOF.
                    while (inputFile.get(ch) && ch != '\n');
                    if (ch == '\n') {
                        currentLine++;
                    }
                    // Loop back to the START state to find the next token.
                    continue; 
                }
                inputFile.unget(); // Otherwise, it's a single '/' (Division)[cite: 143].
                return {OP_DIV, "/", currentLine};

            default:
                // If the character doesn't match any rule.
                return {TOKEN_ERROR, string("Unknown character: ") + ch, currentLine};
        }
    }

    // If the loop finishes, we reached EOF.
    return {END_OF_FILE, "EOF", currentLine};
}

// --- MAIN EXECUTION ---
int main() {
 
    string inputFileName = "source.mj";
    string outputFileName = "tokens.txt";

    // 2. Open Files
    inputFile.open(inputFileName);
    outputFile.open(outputFileName);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input file " << inputFileName << endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open output file " << outputFileName << endl;
        return 1;
    }

    cout << "Lexical Analysis started. Reading from " << inputFileName << "..." << endl;
    cout << "Token stream being written to " << outputFileName << endl;

    // 3. Tokenization Loop
    Token token;
    do {
        token = getNextToken();
        outputToken(token); // Output token to the file.
        
        // Critical error check: Stop on unrecoverable errors.
        if (token.type == TOKEN_ERROR) {
            cerr << "\nLEXICAL ERROR at line " << token.line << ": " << token.lexeme << endl;
            break;
        }

    } while (token.type != END_OF_FILE);

    // 4. Cleanup
    inputFile.close();
    outputFile.close();

    cout << "\nLexical Analysis complete. Check " << outputFileName << " for the results." << endl;
    return 0;
}