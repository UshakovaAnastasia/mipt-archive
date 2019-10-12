#ifndef BRACKETSEQ_H
#define BRACKETSEQ_H

extern char openBrackets [];
extern char closeBrackets [];

int findPositionOfOpen (char character);
int findPositionOfClose (char character);
bool BracketsMatch(char open, char close);
bool OpenBracket(char bracket);
bool CloseBracket(char bracket);
bool CheckBracketSequence(char * s);

#endif
