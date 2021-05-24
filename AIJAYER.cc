#include "Player.hh"
#include <climits>

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME JAYER


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
//Guardar enemigos
typedef vector<int> VI;
typedef vector<VI> VVI;

//Guardar cells
typedef vector<char> VC;
typedef vector <VC> VVC;

typedef vector < vector<bool> > VVB;
typedef vector < vector<Dir> > dirs;
VVB visitado;

/*
//Comprueba que las tropas de sauron están a 4 de distancia como minimo
Pos not_sauron(Pos p){
    VVB visitados(60,vector <bool>(60,false));
    int dist = 0;
    queue<Pos> q;
    q.push(p);
    visitados[p.i][p.j] = true;
    while(!q.empty()){
        Pos pos = q.front();
        q.pop();
        if(cell(pos).id != -1 and (unit(cell(pos).id).type == Troll or unit(cell(pos).id).type == Balrog) and dist < 4) return pos;
        for(int i = 0; i < 8; ++i){
            if(i == 0) ++dist;
            Pos pos_aux = pos + Dir(i);
            if(pos_ok(pos_aux) and not visitados[pos_aux.i][pos_aux.j]){
                q.push(pos_aux);
                visitados[p.i][p.j] = true;
            }
        }
    }
    Pos pmal(70, 70);
    return pmal;
}*/
Pos bfs_sauron(int id, Pos p){
    VVB visitats(60, vector<bool>(60, false));
    VVI distancia(60, vector<int>(60, INT_MAX));
        queue<Pos> q;
        q.push(p);
        distancia[p.i][p.j] = 0;
        visitats[p.i][p.j] = true;
        while(!q.empty()){
            Pos paux = q.front();
            q.pop();
            if(distancia[paux.i][paux.j] < 5 and cell(paux).id != -1 and (unit(cell(paux).id).type == Balrog or unit(cell(paux).id).type == Troll))  return paux;
            for(int w = 0; w < 8; ++w){
                Dir d = Dir(w);
                Pos pos = paux + d;
                if(pos_ok(pos) and not visitats[pos.i][pos.j] and (cell(pos).type == Cave or cell(pos).type == Outside)){
                    visitats[pos.i][pos.j] = true;
                    if(distancia[pos.i][pos.j] > distancia[paux.i][paux.j] + 1){
                          distancia[pos.i][pos.j] = distancia[paux.i][paux.j] + 1;
                          q.push(pos);
                    }
                }
            }
        }
        Pos pmal(70, 70);
        return pmal;
}

//Si hay tropas de sauron cerca, me dice que dirección es segura.
int huir_malos(int id, Pos M){
    Pos Y = unit(id).pos;
      if(M.i > Y.i and M.j < Y.j){
          if(pos_ok(Y + Top) and (cell(Y + Top).type == Outside or cell(Y + Top).type == Cave)) return 4;
          else if(pos_ok(Y + RT) and (cell(Y + RT).type == Outside or cell(Y + RT).type == Cave)) return 3;
          else if(pos_ok(Y + Right) and (cell(Y + Right).type == Outside or cell(Y + Right).type == Cave)) return 2;
      }
      else if(M.i > Y.i and M.j > Y.j){
          if(pos_ok(Y + Top) and (cell(Y + Top).type == Outside or cell(Y + Top).type == Cave)) return 4;
          else if(pos_ok(Y + TL) and (cell(Y + TL).type == Outside or cell(Y + TL).type == Cave)) return 5;
          else if(pos_ok(Y + Left) and (cell(Y + Left).type == Outside or cell(Y + Left).type == Cave)) return 6;
      }
      else if(M.i > Y.i and M.j == Y.j){
          if(pos_ok(Y + Top) and (cell(Y + Top).type == Outside or cell(Y + Top).type == Cave)) return 4;
          else if(pos_ok(Y + TL) and (cell(Y + TL).type == Outside or cell(Y + TL).type == Cave)) return 5;
          else if(pos_ok(Y + RT) and (cell(Y + RT).type == Outside or cell(Y + RT).type == Cave)) return 6;
      }
      else if(M.i < Y.i and M.j == Y.j){
          if(pos_ok(Y + Bottom) and (cell(Y + Bottom).type == Outside or cell(Y + Bottom).type == Cave)) return 0;
          else if(pos_ok(Y + LB) and (cell(Y + LB).type == Outside or cell(Y + LB).type == Cave)) return 7;
          else if(pos_ok(Y + BR) and (cell(Y + BR).type == Outside or cell(Y + BR).type == Cave)) return 1;
      }
      else if(M.i < Y.i and M.j < Y.j){
          if(pos_ok(Y + Bottom) and (cell(Y + Bottom).type == Outside or cell(Y + Bottom).type == Cave)) return 0;
          else if(pos_ok(Y + Right) and (cell(Y + Right).type == Outside or cell(Y + Right).type == Cave)) return 2;
          else if(pos_ok(Y + BR) and (cell(Y + BR).type == Outside or cell(Y + BR).type == Cave)) return 1;
      }
      else if(M.i < Y.i and M.j > Y.j){
          if(pos_ok(Y + Bottom) and (cell(Y + Bottom).type == Outside or cell(Y + Bottom).type == Cave)) return 0;
          else if(pos_ok(Y + Left) and (cell(Y + Left).type == Outside or cell(Y + Left).type == Cave)) return 6;
          else if(pos_ok(Y + LB) and (cell(Y + LB).type == Outside or cell(Y + LB).type == Cave)) return 7;
      }
      else if(M.i == Y.i and M.j > Y.j){
          if(pos_ok(Y + Left) and (cell(Y + Left).type == Outside or cell(Y + Left).type == Cave)) return 6;
          else if(pos_ok(Y + LB) and (cell(Y + LB).type == Outside or cell(Y + LB).type == Cave)) return 7;
          else if(pos_ok(Y + TL) and (cell(Y + TL).type == Outside or cell(Y + TL).type == Cave)) return 5;
      }
      else if(M.i == Y.i and M.j < Y.j){
          if(pos_ok(Y + Right) and (cell(Y + Right).type == Outside or cell(Y + Right).type == Cave)) return 2;
          else if(pos_ok(Y + RT) and (cell(Y + RT).type == Outside or cell(Y + RT).type == Cave)) return 6;
          else if(pos_ok(Y + BR) and (cell(Y + BR).type == Outside or cell(Y + BR).type == Cave)) return 1;
      }
      return 8;
}




struct dist_pos_dir{
  int dist;
  Pos p;
  Dir d;

  friend bool operator> (const dist_pos_dir& dps, const dist_pos_dir& dps2){
    return dps.dist > dps2.dist;
  }
};



Dir bfs_tesoros(int id, Pos p){
    VVB visitats(60, vector<bool>(60, false));
    VVI distancia(60, vector<int>(60, INT_MAX));
    dirs direc(60, vector<Dir>(60));
    priority_queue<dist_pos_dir, vector<dist_pos_dir>, greater<dist_pos_dir> > q;
    dist_pos_dir dpd;
        dpd.dist = 0;
        dpd.p = p;
        dpd.d = None;
        q.push(dpd);
        distancia[p.i][p.j] = 0;
        visitats[p.i][p.j] = true;
        while(!q.empty()){
            Pos paux = q.top().p;
            q.pop();
            if(distancia[paux.i][paux.j] != 1 and distancia[paux.i][paux.j] < 45 and cell(paux).treasure) return direc[paux.i][paux.j];
            if(distancia[paux.i][paux.j] == 1 and cell(paux).id == -1 and cell(paux).treasure) return direc[paux.i][paux.j];
            for(int w = 0; w < 8; ++w){
                Dir d = Dir(w);
                Pos pos = paux + d;
                if(pos_ok(pos) and not visitats[pos.i][pos.j]){
                    visitats[pos.i][pos.j] = true;
                    if(distancia[pos.i][pos.j] > distancia[paux.i][paux.j] + 1){
                        if(distancia[paux.i][paux.j] == 0) direc[paux.i][paux.j] = d;
                        if(cell(pos).type == Rock) distancia[pos.i][pos.j] = distancia[paux.i][paux.j] + 1 + cell(pos).turns;
                        if(cell(pos).type == Abyss or cell(pos).type == Granite) distancia[pos.i][pos.j] = INT_MAX;
                        if(cell(pos).type == Cave or cell(pos).type == Outside) distancia[pos.i][pos.j] = distancia[paux.i][paux.j] + 1;
                        if(distancia[paux.i][paux.j] == 0 and cell(pos).id != -1) distancia[pos.i][pos.j] = INT_MAX;
                        if(distancia[pos.i][pos.j] != INT_MAX){
                          dpd.dist = distancia[pos.i][pos.j];
                          dpd.p = pos;
                          dpd.d = d;
                          q.push(dpd);
                        }
                        direc[pos.i][pos.j] = direc[paux.i][paux.j];
                    }
                }
            }
        }
        return None;
}


Dir bfs_casillas(int id, Pos p){
    VVB visitats(60, vector<bool>(60, false));
    VVI distancia(60, vector<int>(60, INT_MAX));
    dirs direc(60, vector<Dir>(60));
        queue<pair<Pos, Dir> > q;
        q.push(make_pair(p, None));
        distancia[p.i][p.j] = 0;
        visitats[p.i][p.j] = true;
        while(!q.empty()){
            Pos paux = q.front().first;
            q.pop();
            if(cell(paux).owner != me() and distancia[paux.i][paux.j] != 1 and cell(paux).type == Cave) return direc[paux.i][paux.j];
            if(cell(paux).owner != me() and distancia[paux.i][paux.j] == 1 and cell(paux).id == -1 and cell(paux).type == Cave) return direc[paux.i][paux.j];
            for(int w = 0; w < 8; ++w){
                Dir d = Dir(w);
                Pos pos = paux + d;
                if(pos_ok(pos) and not visitats[pos.i][pos.j] and (cell(pos).type == Cave or cell(pos).type == Outside)){
                    visitats[pos.i][pos.j] = true;
                    if(distancia[pos.i][pos.j] > distancia[paux.i][paux.j] + 1){
                        if(distancia[paux.i][paux.j] == 0) direc[paux.i][paux.j] = d;
                            distancia[pos.i][pos.j] = distancia[paux.i][paux.j] + 1;
                            q.push(make_pair(pos, d));
                            direc[pos.i][pos.j] = direc[paux.i][paux.j];
                    }
                }
            }
        }
}

Dir bfs_atacar(int id, Pos p){
    VVB visitats(60, vector<bool>(60, false));
    VVI distancia(60, vector<int>(60, INT_MAX));
    dirs direc(60, vector<Dir>(60));
        queue<pair<Pos, Dir> > q;
        q.push(make_pair(p, None));
        distancia[p.i][p.j] = 0;
        visitats[p.i][p.j] = true;
        while(!q.empty()){
            Pos paux = q.front().first;
            q.pop();
            if(distancia[paux.i][paux.j] < 3 and cell(paux).id != -1 and unit(cell(paux).id).player != me() and
              (unit(cell(paux).id).type == Dwarf or unit(cell(paux).id).type == Wizard or (unit(cell(paux).id).type == Orc and unit(cell(paux).id).health < unit(id).health)))  return direc[paux.i][paux.j];
            for(int w = 0; w < 8; ++w){
                Dir d = Dir(w);
                Pos pos = paux + d;
                if(pos_ok(pos) and not visitats[pos.i][pos.j] and (cell(pos).type == Cave or cell(pos).type == Outside)){
                    visitats[pos.i][pos.j] = true;
                    if(distancia[pos.i][pos.j] > distancia[paux.i][paux.j] + 1){
                        if(distancia[paux.i][paux.j] == 0) direc[paux.i][paux.j] = d;
                            distancia[pos.i][pos.j] = distancia[paux.i][paux.j] + 1;
                            q.push(make_pair(pos, d));
                            direc[pos.i][pos.j] = direc[paux.i][paux.j];
                    }
                }
            }
        }
        return None;
}

Dir bfs_wizards(int id, Pos p){
    VVB visitats(60, vector<bool>(60, false));
    VVI distancia(60, vector<int>(60, INT_MAX));
    dirs direc(60, vector<Dir>(60));
        queue<pair<Pos, Dir> > q;
        q.push(make_pair(p, None));
        distancia[p.i][p.j] = 0;
        visitats[p.i][p.j] = true;
        while(!q.empty()){
            Pos paux = q.front().first;
            q.pop();
            if(distancia[paux.i][paux.j] < 25 and distancia[paux.i][paux.j] > 0 and cell(paux).id != -1 and unit(cell(paux).id).player == me() and unit(cell(paux).id).type == Dwarf)  return direc[paux.i][paux.j];
            for(int w = 0; w < 8; w = w + 2){
                Dir d = Dir(w);
                Pos pos = paux + d;
                if(pos_ok(pos) and not visitats[pos.i][pos.j] and (cell(pos).type == Cave or cell(pos).type == Outside)){
                    visitats[pos.i][pos.j] = true;
                    if(distancia[pos.i][pos.j] > distancia[paux.i][paux.j] + 1){
                        if(distancia[paux.i][paux.j] == 0) direc[paux.i][paux.j] = d;
                            distancia[pos.i][pos.j] = distancia[paux.i][paux.j] + 1;
                            q.push(make_pair(pos, d));
                            direc[pos.i][pos.j] = direc[paux.i][paux.j];
                    }
                }
            }
        }
        return None;
}



void move_wizards(int id) {
    command(id, bfs_wizards(id, unit(id).pos));
}

void move_dwarves(int id) {
        /*Pos p = bfs_sauron(id, unit(id).pos);
        if(not pos_ok(p)){*/
          Dir d = bfs_atacar(id, unit(id).pos);
          if(d != None) command(id, d);
          else{
            Dir d1 = bfs_tesoros(id, unit(id).pos);
            if(d1 != None) command(id, d1);
            else{
              command(id, bfs_casillas(id, unit(id).pos));
            }
        }
      /*}else{
        Dir d = Dir(huir_malos(id, p));
        command(id, d);
      }*/
    }





  /**
   * Play method, invoked once per each round.
   */
 virtual void play () {
        VI mis_enanos = dwarves(me());
        for(int e: mis_enanos){
            move_dwarves(e);
        }
        VI mis_magos = wizards(me());
        for(int a: mis_magos){
            move_wizards(a);
        }
    }
};
/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
