#include <stdio.h>
#include <iostream>
#include "utf8cpp/utf8.h"
#include <cstring>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

std::map<std::string, int> vocab;

bool IsStopWord(const std::string& lexeme){
  static std::set<std::string> stop_words = {
    "de", "a", "o", "que", "e", "do", "da", "em", "um", "para", "e", "com", 
    "nao", "uma", "os", "no", "se", "na", "por", "mais", "as", "dos", "como", 
    "mas", "foi", "ao", "ele", "das", "tem", "seu", "sua", "ou", "ser", "quando", 
    "muito", "ha", "nos", "ja", "esta", "eu", "tambem", "so", "pelo", "pela", "ate", 
    "isso", "ela", "entre", "era", "depois", "sem", "mesmo", "aos", "ter", "seus", 
    "quem", "nas", "me", "esse", "eles", "estao", "voce", "tinha", "foram", "essa", 
    "num", "nem", "suas", "meu", "às", "minha", "tem", "numa", "pelos", "elas", 
    "havia", "seja", "qual", "sera", "nos", "tenho", "lhe", "deles", "essas", "esses", 
    "pelas", "este", "fosse", "dele", "tu", "te", "voces", "vos", "lhes", "meus", "minhas", 
    "teu", "tua", "teus", "tuas", "nosso", "nossa", "nossos", "nossas", "dela", "delas", "esta", 
    "estes", "estas", "aquele", "aquela", "aqueles", "aquelas", "isto", "aquilo", "estou", 
    "esta", "estamos", "estao", "estive", "esteve", "estivemos", "estiveram", "estava", "estavamos", 
    "estavam", "estivera", "estiveramos", "esteja", "estejamos", "estejam", "estivesse", "estivessemos", 
    "estivessem", "estiver", "estivermos", "estiverem", "hei", "há", "havemos", "hao", "houve", 
    "houvemos", "houveram", "houvera", "houveramos", "haja", "hajamos", "hajam", "houvesse", 
    "houvessemos", "houvessem", "houver", "houvermos", "houverem", "houverei", "houvera", "houveremos", 
    "houverao", "houveria", "houveriamos", "houveriam", "sou", "somos", "sao", "era", "eramos", "eram", 
    "fui", "foi", "fomos", "foram", "fora", "foramos", "seja", "sejamos", "sejam", "fosse", "fossemos", 
    "fossem", "for", "formos", "forem", "serei", "sera", "seremos", "serao", "seria", "seriamos", 
    "seriam", "tenho", "tem", "temos", "tem", "tinha", "tinhamos", "tinham", "tive", "teve", "tivemos", 
    "tiveram", "tivera", "tiveramos", "tenha", "tenhamos", "tenham", "tivesse", "tivéssemos", "tivessem", 
    "tiver", "tivermos", "tiverem", "terei", "tera", "teremos", "terao", "teria", "teriamos", "teriam",

    // English.
    "about", "above", "above", "across", "after", "afterwards", "again", "against", "all", 
    "almost", "alone", "along", "already", "also","although","always","am","among", "amongst", 
    "amoungst", "amount",  "an", "and", "another", "any","anyhow","anyone","anything","anyway", 
    "anywhere", "are", "around", "as",  "at", "back","be","became", "because","become","becomes", 
    "becoming", "been", "before", "beforehand", "behind", "being", "below", "beside", "besides", 
    "between", "beyond", "bill", "both", "bottom","but", "by", "call", "can", "cannot", "cant", 
    "co", "con", "could", "couldnt", "cry", "de", "describe", "detail", "do", "done", "down", 
    "due", "during", "each", "eg", "eight", "either", "eleven","else", "elsewhere", "empty", 
    "enough", "etc", "even", "ever", "every", "everyone", "everything", "everywhere", "except", 
    "few", "fifteen", "fify", "fill", "find", "fire", "first", "five", "for", "former", "formerly", 
    "forty", "found", "four", "from", "front", "full", "further", "get", "give", "go", "had", "has", 
    "hasnt", "have", "he", "hence", "her", "here", "hereafter", "hereby", "herein", "hereupon", "hers", 
    "herself", "him", "himself", "his", "how", "however", "hundred", "ie", "if", "in", "inc", "indeed", 
    "interest", "into", "is", "it", "its", "itself", "keep", "last", "latter", "latterly", "least", 
    "less", "ltd", "made", "many", "may", "me", "meanwhile", "might", "mill", "mine", "more", 
    "moreover", "most", "mostly", "move", "much", "must", "my", "myself", "name", "namely", "neither", 
    "never", "nevertheless", "next", "nine", "no", "nobody", "none", "noone", "nor", "not", "nothing", 
    "now", "nowhere", "of", "off", "often", "on", "once", "one", "only", "onto", "or", "other", "others", 
    "otherwise", "our", "ours", "ourselves", "out", "over", "own","part", "per", "perhaps", "please", 
    "put", "rather", "re", "same", "see", "seem", "seemed", "seeming", "seems", "serious", "several", 
    "she", "should", "show", "side", "since", "sincere", "six", "sixty", "so", "some", "somehow", 
    "someone", "something", "sometime", "sometimes", "somewhere", "still", "such", "system", "take", 
    "ten", "than", "that", "the", "their", "them", "themselves", "then", "thence", "there", "thereafter", 
    "thereby", "therefore", "therein", "thereupon", "these", "they", "thickv", "thin", "third", "this", 
    "those", "though", "three", "through", "throughout", "thru", "thus", "to", "together", "too", "top", 
    "toward", "towards", "twelve", "twenty", "two", "un", "under", "until", "up", "upon", "us", "very", 
    "via", "was", "we", "well", "were", "what", "whatever", "when", "whence", "whenever", "where", 
    "whereafter", "whereas", "whereby", "wherein", "whereupon", "wherever", "whether", "which", 
    "while", "whither", "who", "whoever", "whole", "whom", "whose", "why", "will", "with", "within", 
    "without", "would", "yet", "you", "your", "yours", "yourself", "yourselves", "the"
  };

  if (lexeme.size() <= 1 || lexeme.size() >= 30) return true;
  return stop_words.find(lexeme) != stop_words.end();
}

char GetValidCharacter(int c) {
  if (c >= 0x41 && c <= 0x5A) { // A-Z to a-z.
    return c + 0x20;
  } else if (c >= 0x61 && c <= 0x7A) { // a-z remains a-z.
    return c;
  } else if (c >= 0xC0 && c <= 0xFF) { // Accented characters to unaccented.
    static const char*
    //   "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"
    tr = "aaaaaaeceeeeiiiidnoooooxouuuuypsaaaaaaeceeeeiiiionooooooouuuuypy";
    return tr[c - 0xC0];
  } else { // Non alphanumeric characters to null.
    return '\0';
  }
}

std::vector<std::string> ExtractLexemes(std::string text) {
  vector<std::string> result;
  
  std::string lexeme;
  std::string::iterator current_it = text.begin();
  
  int utf8char;
  while (current_it != text.end()) {
    utf8char = utf8::next(current_it, text.end());
    char c = GetValidCharacter(utf8char);
    if (c != '\0') {
      lexeme += c;
    } else if (lexeme.length() > 0 && lexeme.length() < 256) {
      result.push_back(lexeme);
      lexeme.clear();
    } else {
      lexeme.clear();
    }
  }
  
  if (lexeme.length() > 0 && lexeme.length() < 256)
    result.push_back(lexeme);
  return result;
}

int main (int argc, char* argv[]) {
  std::string line;
  std::ifstream f(argv[1]);
  if (!f.is_open()) {
    std::cout << "Could not open file" << std::endl;
    return 1;
  }

  while (std::getline(f, line)) {
    std::vector<std::string> tokens = ExtractLexemes(line);
    for (auto token : tokens) {
      if (vocab.find(token) == vocab.end()) {
        vocab[token] == 1;
      } else {
        vocab[token]++;
      }
    }
  }
  f.close();

  std::vector<std::pair<std::string, int>> token_vec;
  for (auto token : vocab) {
    if (!IsStopWord(token.first))
      token_vec.push_back(token);
  }

  sort(token_vec.begin(), token_vec.end(), 
    []( 
      const std::pair<std::string, int>& a, 
      const std::pair<std::string, int>& b
    ) -> bool { 
    return a.second > b.second; 
  });

  for (auto token : token_vec) {
    if (IsStopWord(token.first)) {
      std::cout << token.first << " " << token.second + 1 << ", STOPWORD" << std::endl;
    } else {
      std::cout << token.first << " " << token.second + 1 << std::endl;
    }
  }
  return 0;
}
