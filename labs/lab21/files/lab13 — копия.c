#include<stdio.h>

enum state{
    SEARCH_WORD,
    BUILD_SET_OF_LETTERS_AND_COMPARISON,
};

enum state state=SEARCH_WORD;

int sep(int symbol){
    if (symbol==' ' || symbol==',' || symbol=='\t' || symbol=='\n' || symbol==EOF){
        return 1;
    } 
    return 0;
}

int letter_num(int c){
    if(c>='a' && c<='z'){
        return c-'a';
    } else if(c>='A' && c<='Z'){
        return c-'A';
    }
    return -1;
}

int set_from_letter(int c){
    int sequence_number=letter_num(c);
    if(sequence_number>=0){
        return 1 << sequence_number;
    } 
    return 0;
}

int main(){
    int number_of_matching_words_pairs=0;
    int set_of_letters_of_old_word=0;
    int set_of_letters_of_new_word=0;
    int set_of_consonat_letters=0;
    int set_of_vowel_letters=0;
    int set_letters=0;
    int symbol;
    set_letters = (1 << 26)-1;
    set_of_vowel_letters = set_from_letter('a') | set_from_letter('e') | set_from_letter('i') | set_from_letter('o') | set_from_letter('u') | set_from_letter('y');
    set_of_consonat_letters= set_letters & ~set_of_vowel_letters;
    do {
        symbol=getchar();
        if(state==SEARCH_WORD){
            if(sep(symbol)){
                state=SEARCH_WORD;
            } else {
                set_of_letters_of_new_word |= set_from_letter(symbol);
                state=BUILD_SET_OF_LETTERS_AND_COMPARISON;
            }
        } else if(state==BUILD_SET_OF_LETTERS_AND_COMPARISON){
            if(sep(symbol)){
                set_of_letters_of_new_word = set_of_letters_of_new_word&set_of_consonat_letters;
                if(set_of_letters_of_new_word && set_of_letters_of_new_word==set_of_letters_of_old_word){
                    number_of_matching_words_pairs++;
                }
                set_of_letters_of_old_word=set_of_letters_of_new_word;
                set_of_letters_of_new_word=0;
                state=SEARCH_WORD;
            } else {
                set_of_letters_of_new_word |= set_from_letter(symbol);
                state=BUILD_SET_OF_LETTERS_AND_COMPARISON;
            }
        }

    } while(symbol!=EOF);
    printf("Количество пар соседних слов, у которых согласные совподают: %d\n", number_of_matching_words_pairs);
}