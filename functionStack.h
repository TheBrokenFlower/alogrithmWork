#ifndef TEAM_ALGORITHM_FUNCTIONSTACK_H
#define TEAM_ALGORITHM_FUNCTIONSTACK_H

inline int getLen (int x) {
    int tot = 0;
    while (x) {
        x /= 10;
        tot++;
    }
    tot = std::max (tot, (int)1);
    return tot;
}

struct funcElement {
    std::string name;
    std::vector <int> vec;
    funcElement () {}
    funcElement (std::string _name, std::vector <int> _vec) {
        name = _name;
        for (auto x : _vec)
            vec.push_back (x);
    }
    inline void print () {
        std::cout << name << "( ";
        for (int i = 0; i < vec.size (); i++) {
            if (i == vec.size () - 1) {
                std::cout << vec[i] << " )";
            } else {
                std::cout << vec[i] << ", ";
            }
        }
    }
    inline int memSize () {
        return sizeof (int) * vec.size ();
    }
    inline int width () {
        int ret = 0;
        ret += name.size ();
        ret += 2;
        for (auto x : vec) {
            ret += getLen (x);
            ret += 2;
        }
        return ret;
    }
};

struct funcStack {
    int memCost;
    std::vector <funcElement> vec;
    funcStack () {}
    funcStack (std::vector <funcElement> _vec) {
        for (auto x : _vec)
            this->vec.push_back (x);
    }
    inline void print () {
        system ("cls");
        for (int i = 1; i <= 20 - 2 * (vec.size () + 1); i++)
            std::cout << std::endl;
        int maxLen = 20;
        for (auto x : vec) {
            maxLen = std::max (maxLen, x.width ());
        }
        std::cout << "| ";
        for (int i = 1; i <= maxLen; i++)
            std::cout << " ";
        std::cout << " |" << std::endl;
        for (auto it = vec.rbegin(); it != vec.rend (); it++) {
            auto x = *it;
            std::cout << "|";
            for (int i = 1; i <= maxLen + 2; i++)
                std::cout << "_";
            std::cout << "|" << std::endl;
            std::cout << "|";
            int wide = x.width ();
            int spaceLen = (maxLen + 2 - wide) / 2;
            for (int i = 1; i <= spaceLen; i++) {
                std::cout << " ";
            }
            x.print ();
            for (int i = 1; i <= maxLen + 2 - spaceLen - wide; i++) {
                std::cout << " ";
            }
            std::cout << "|" << std::endl;
        }
        for (int i = 1; i <= maxLen + 4; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
        Sleep (1000);
    }
    inline bool empty () {
        return this->vec.empty ();
    }
    funcElement top () {
        return vec[vec.size () - 1];
    }
    void push (funcElement x) {
        std::cout << "push" << std::endl;
        vec.push_back (x);
        this->print ();
    }
    void pop () {
        std::cout << "pop" << std::endl;
        vec.pop_back ();
        this->print ();
    }
    int executeBin (int L, int R, int x) {
        std::vector <int> tempVec;
        tempVec.push_back (L);
        tempVec.push_back (R);
        tempVec.push_back (x);
        funcElement fE ((std::string)"binSearch", tempVec);
        this->push (fE);
        int ret = -1;
        while (!this->empty ()) {
            auto nowd = this->top ();
            this->pop ();
            if (nowd.vec[0] > nowd.vec[1])
                return -1;
            int mid = (nowd.vec[0] + nowd.vec[1]) >> 1;
            if (arr[mid] == nowd.vec[2]) {
                return mid;
            } else if (arr[mid] < x) {
                auto newd = nowd;
                newd.vec[0] = mid + 1;
                this->push (newd);
            } else {
                auto newd = nowd;
                newd.vec[1] = mid - 1;
                this->push (newd);
            }
        }
        return -1;
    }
} FuncStack;

int recursiveTot, maxRecusiveTot;
int executeTot;

int memDfs (int i, int j) {
    executeTot++;
    if (i == 0)
        return 0;
    recursiveTot++;
    maxRecusiveTot = std::max (maxRecusiveTot, recursiveTot);
    funcElement fE;
    fE.name = "memDfs";
    std::vector <int> vec;
    vec.push_back (i);
    vec.push_back (j);
    fE.vec = vec;
    if (vis[i][j]) {
        recursiveTot--;
        return f[i][j];
    }
    FuncStack.push (fE);
    if (j >= weight[i]) {
        f[i][j] = std::max (memDfs (i - 1, j), memDfs (i - 1, j - weight[i]) + val[i]);
    } else {
        f[i][j] = memDfs (i - 1, j);
    }
    vis[i][j] = true;
    FuncStack.pop ();
    recursiveTot--;
    return f[i][j];
}

#endif //TEAM_ALGORITHM_FUNCTIONSTACK_H
