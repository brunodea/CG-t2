#ifndef _BRUNODEA_CG_T2_PLAYER_H_
#define _BRUNODEA_CG_T2_PLAYER_H_

/*
 * Classe do jogador. Eh apenas uma especificacao da classe ship.
 * a diferenca eh que o usuario pode mover a nave.
 */

#include "Game/Ship.hpp"

namespace Game
{
    class Player : public Ship
    {
    public:
        Player();
        Player(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos);

        /* função chamada após o update básico de Ship. */
        void update();
        void onCollision(GameObject *obj);
        void onKeyEvent(int key, int state);
        void onMouseButtonEvent(int button, int action);

    private:
        void init();
    }; //end of class Player.
} //end of namespace Player.

#endif
