bool isValid(char* s) {
    char buffer[10000];
    char* currLoc = buffer;

    while(1) {
        if(*s == '\0') {
            if(currLoc == buffer) {
                return true;
            } else {
                return false;
            }
        } else if(*s == '(') {
            *currLoc = '(';
            currLoc = currLoc + sizeof(char);
        } else if (*s == '[') {
            *currLoc = '[';
            currLoc = currLoc + sizeof(char);
        } else if (*s == '{') {
            *currLoc = '{';
            currLoc = currLoc + sizeof(char);
        } else if (*s == ')') {
            currLoc = currLoc - sizeof(char);
            if(currLoc < buffer) {
                return false;
            }
            if(*currLoc != '(') {
                return false;
            }
        } else if (*s == ']') {
            currLoc = currLoc - sizeof(char);
            if(currLoc < buffer) {
                return false;
            }
            if(*currLoc != '[') {
                return false;
            }
        } else if (*s == '}') {
            currLoc = currLoc - sizeof(char);
            if(currLoc < buffer) {
                return false;
            }
            if(*currLoc != '{') {
                return false;
            }
        }
        
        s = s + sizeof(char);
    }
}
