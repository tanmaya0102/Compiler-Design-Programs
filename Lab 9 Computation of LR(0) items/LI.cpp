#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef map<char, vector<string> > AugmentedGrammar;
typedef map<string, int> GotoMap; // <aps productions to LR(0) item ids

// structy for representing an augmented grammar production
struct AugmentedProduction
{
    char lhs;   // left hand side of production
    string rhs; // right hand side of production

    AugmentedProduction() {}
    AugmentedProduction(char _lhs, string _rhs) : lhs(_lhs), rhs(_rhs) {}
};

// Class for representing LR(0) items.
class LR0Item
{
private:
    // list of productions
    vector<AugmentedProduction*> productions;

public:
    // list of out-edges
    map<char, int> gotos;

    // constructor
    LR0Item() {}
    // destructor
    ~LR0Item() {}

    // add production
    void Push(AugmentedProduction *p) { productions.push_back(p); }
    // return the number of productions
    int Size() { return int(productions.size()); }

    // return whether or not this item contains the production prodStr
    bool Contains (string production) {
        for (auto it = productions.begin(); it != productions.end(); it++) {
            string existing = string(&(*it)->lhs, 1) + "->" + (*it)->rhs;
            if (strcmp(production.c_str(), existing.c_str()) == 0) {
                return true;
            }
        }
        return false;
    }

    // overloaded index operator; access pointer to production.
    AugmentedProduction* operator[](const int index) {
        return productions[index];
    }
};

/* void add_closure
 * If 'next' is the current input symbol and next is nonterminal, then the set
 * of LR(0) items reachable from here on next includes all LR(0) items reachable
 * from here on FIRST(next). Add all grammar productions with a lhs of next */
void
add_closure(char lookahead, LR0Item& item, AugmentedGrammar& grammar)
{
    // only continue if lookahead is a non-terminal
    if (!isupper(lookahead)) return;

    string lhs = string(&lookahead, 1);
    // iterate over each grammar production beginning with p->rhs[next]
    // to see if that production has already been included in this item.
    for (int i = 0; i<grammar[lookahead].size(); i++) {
        string rhs = "." + grammar[lookahead][i];
        // if the grammar production for the next input symbol does not yet
        // exist for this item, add it to the item's set of productions
        if (!item.Contains( lhs + "->" + rhs )) {
            item.Push(new AugmentedProduction(lookahead, rhs));
        }
    }
}

// produce the graph of LR(0) items from the given augmented grammar
void
get_LR0_items(vector<LR0Item>& lr0items, AugmentedGrammar& grammar, int& itemid, GotoMap& globalGoto)
{
    printf("I%d:\n", itemid);

    // ensure that the current item contains te full closure of it's productions
    for (int i = 0; i<lr0items[itemid].Size(); i++) {
        string rhs = lr0items[itemid][i]->rhs;
        char lookahead = rhs[rhs.find('.')+1];
        add_closure(lookahead, lr0items[itemid], grammar);
    }

    int nextpos;
    char lookahead, lhs;
    string rhs;
    AugmentedProduction *prod;

    // iterate over each production in this LR(0) item
    for (int i = 0; i<lr0items[itemid].Size(); i++) {
        // get the current production
        lhs = lr0items[itemid][i]->lhs;
        rhs = lr0items[itemid][i]->rhs;
        string production = string(&lhs,1) + "->" + rhs;

        // get lookahead if one exists
        lookahead = rhs[rhs.find('.')+1];
        if (lookahead == '\0') {
            printf("\t%-20s\n", &production[0]);
            continue;
        }

        // if there is no goto defined for the current input symbol from this
        // item, assign one.
        if (lr0items[itemid].gotos.find(lookahead) == lr0items[itemid].gotos.end()) {
            // that one instead of creating a new one
            // if there is a global goto defined for the entire production, use
            if (globalGoto.find(production) == globalGoto.end()) {
                lr0items.push_back(LR0Item()); // create new state (item)
                // new right-hand-side is identical with '.' moved one space to the right
                string newRhs = rhs;
                int atpos = newRhs.find('.');
                swap(newRhs[atpos], newRhs[atpos+1]);
                // add item and update gotos
                lr0items.back().Push(new AugmentedProduction(lhs, newRhs));
                lr0items[itemid].gotos[lookahead] = lr0items.size()-1;
                globalGoto[production] = lr0items.size()-1;
            } else {
                // use existing global item
                lr0items[itemid].gotos[lookahead] = globalGoto[production];
            }
            printf("\t%-20s goto(%c)=I%d\n", &production[0], lookahead, globalGoto[production]);
        } else {
            // there is a goto defined, add the current production to it
            // move . one space to right for new rhs
            int at = rhs.find('.');
            swap(rhs[at], rhs[at+1]);
            // add production to next item if it doesn't already contain it
            int nextItem = lr0items[itemid].gotos[lookahead];
            if (!lr0items[nextItem].Contains(string(&lhs, 1) + "->" + rhs)) {
                lr0items[nextItem].Push(new AugmentedProduction(lhs, rhs));
            }
            swap(rhs[at], rhs[at+1]);
            printf("\t%-20s\n", &production[0]);
        }
    }
}

/**
 * void load_grammar
 * scan and load the grammar from stdin while setting first LR(0) item */
void load_grammar(AugmentedGrammar& grammar, vector<LR0Item>& lr0items)
{
    string production;
    string lhs, rhs;
    string delim = "->";
    
    getline(cin, lhs); // scan start production
    grammar['\''].push_back(lhs);
    lr0items[0].Push(new AugmentedProduction('\'', "." + lhs));
    printf("'->%s\n", lhs.c_str());

    while(1) {
        getline(cin, production);
        if (production.length() < 1) return;

        auto pos = production.find(delim);
        if(pos!=string::npos){
            lhs = production.substr(0,pos);
            rhs = production.substr(pos+delim.length(),std::string::npos);
        }
        
        grammar[lhs[0]].push_back(rhs);
        printf("%s->%s\n", lhs.c_str(), rhs.c_str());
        lr0items[0].Push(new AugmentedProduction(lhs[0], "." + rhs));
    }
}

// main
int main() {
    int itemid = -1; // counter for the number of LR(0) items
    AugmentedGrammar grammar;
    vector<LR0Item> lr0items = { LR0Item() }; // push start state
    GotoMap globalGoto;

    printf("Augmented Grammar\n");
    printf("-----------------\n");
    load_grammar(grammar, lr0items);
    printf("\n");

    printf("Sets of LR(0) Items\n");
    printf("-------------------\n");
    while (++itemid < int(lr0items.size())) {
        get_LR0_items(lr0items, grammar, itemid, globalGoto);
    }
    printf("\n");
    return 0;
}