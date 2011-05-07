#ifndef _BRUNODEA_CG_T2_GAME_OBJECT_HPP_
#define _BRUNODEA_CG_T2_GAME_OBJECT_HPP_


namespace Game
{
    class GameObject
    {
    public:
        enum Type
        {
            ENEMY,
            PLAYER,
            OBJECT
        }; //end of enum Type.

    public:
        GameObject(Type type) : m_Type(type) {}

        virtual void onRender() = 0;
        virtual void onUpdate() = 0;
        virtual void onCollision(GameObject *obj) = 0;

    private:
        Type m_Type;
    }; //end of class GameObject.
} //end of namespace Game.

#endif
