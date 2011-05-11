#include "Game/GameObject.hpp"
#include "Core/matrix_functions.hpp"

using namespace Game;

GameObject::GameObject()
{
    m_iType = NONE;
    init();
}

GameObject::GameObject(int type) 
    : m_iType(type) 
{ 
    init(); 
}

GameObject::GameObject(const Core::Vector3 &dir, float speed, const Core::Vector3 &pos, int type)
    : m_vDirection3(dir), m_fSpeed(speed), m_vPosition3(pos), m_iType(type)
{
    m_iLifes = 1;
    m_iImage = -1;
    m_bVisible = true;
}

GameObject::~GameObject()
{
}
    
void GameObject::render()
{
    if(!isVisible())
        return;    

    //Descomentar para desenhar o vetor direção e a linha da ponta do mouse à posição do GameObject.
    /*glBegin(GL_LINES);
        glColor4f(1.f, 1.f, 1.f, 1.f);
        glVertex2f(m_vPosition3[0], m_vPosition3[1]);
        glVertex2f(m_Mouse[0],  m_Mouse[1]);

        glColor4f(1.f, 0.f, 0.f, 1.f);
        glVertex2f(m_vPosition3[0], m_vPosition3[1]);
        glVertex2f(m_vPosition3[0]+m_vDirection3[0]*100, m_vPosition3[1]+m_vDirection3[1]*100);

    glEnd();*/

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(1.f, 1.f, 1.f, 1.f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_iImage);
    glBegin(GL_QUADS);
            glTexCoord2f(0.f, 0.f);
            glVertex2f((m_vVertices.at(0)+m_vPosition3)(0,0), (m_vVertices.at(0)+m_vPosition3)(1,0));
            glTexCoord2f(0.f, 1.f);
            glVertex2f((m_vVertices.at(1)+m_vPosition3)(0,0), (m_vVertices.at(1)+m_vPosition3)(1,0));
            glTexCoord2f(1.f, 1.f);
            glVertex2f((m_vVertices.at(2)+m_vPosition3)(0,0), (m_vVertices.at(2)+m_vPosition3)(1,0));
            glTexCoord2f(1.f, 0.f);
            glVertex2f((m_vVertices.at(3)+m_vPosition3)(0,0), (m_vVertices.at(3)+m_vPosition3)(1,0));
    glEnd();

    onRender();
    glDisable(GL_TEXTURE_2D);
}

float GameObject::rotateToDir(bool right)
{
    int toRotate = 1;
    if(!right)
        toRotate *= -1;
    Core::Vector3 perp;
    perp = Core::rotate(MY_PI/2.f)*m_vDirection3; //vetor perpendicular ao vetor direção.

    Core::Vector3 speed;
    speed = m_vDirection3*m_fSpeed;

    Core::Vector3 sum;
    sum = speed + perp;

    float angle = toRotate*Core::angle(m_vDirection3, sum)/15.f;
    rotate(angle);

    return angle;
}

void GameObject::accelerate(bool up)
{
    float v = 1;
    if(!up)
        v *= 1/(-7.f);

    setSpeed(getSpeed() + (v*getAcceleration()));
    if(getSpeed() > getMaxSpeed())
        setSpeed(getMaxSpeed());
    else if(getSpeed() < 0.f)
        setSpeed(0.f);
}

void GameObject::initVertices(float width, float height)
{
    Core::Vector3 v1(1);
    v1[0] = width;
    v1[1] = height;

    Core::Vector3 v2(1);
    v2[0] = width;
    v2[1] = -height;

    Core::Vector3 v3(1);
    v3[0] = -width;
    v3[1] = -height;

    Core::Vector3 v4(1);
    v4[0] = -width;
    v4[1] = height;
    
    std::vector<Core::Vector3> *vec = new std::vector<Core::Vector3>();
    vec->push_back(v1);
    vec->push_back(v2);
    vec->push_back(v3);
    vec->push_back(v4);

    setVertices(*vec);
}

void GameObject::rotate(float angle)
{
    if(angle == 0)
        return;
    Core::Matrix3 rot = Core::rotate(angle);

    Core::Vector3 n_dir = m_vDirection3;
    n_dir = rot*n_dir;
    setDirection(n_dir);
    //Como os vertices ja estao em relação à origem, não precisa transladar para a origem e depois para o lugar certo.
    adjustVertices(rot);

    afterRotate(angle);
}

float GameObject::rotateTo(Core::Vector2 &dot)
{
    Core::Vector2 dir;
    dir[0] = m_vDirection3[0];
    dir[1] = m_vDirection3[1];

    Core::Vector2 pos;
    pos[0] = m_vPosition3[0];
    pos[1] = m_vPosition3[1];

    pos = dot-pos;

    return Core::angle(dir, pos);
}

void GameObject::rotateInDirectionOf(const Core::Vector2 &vec)
{
    Core::Vector2 v;
    v[0] = vec(0, 0);
    v[1] = vec(1, 0);
        
    float ang = rotateTo(v);
    if(ang <= 0.001f)
        return;

    rotate(ang);
    float n_ang = rotateTo(v);
    rotate(-ang);
    float latency = 20.f;
    if(n_ang > 0.001f) //0.001f é uma taxa de erro.
        latency *= -1;

    ang /= latency;
    rotate(ang);

    accelerate(true);
}

bool GameObject::isInSight(const Core::Vector2 &vec)
{
    Core::Vector2 dir;
    dir[0] = m_vDirection3[0];
    dir[1] = m_vDirection3[1];

    Core::Vector2 orig(0);
    Core::Vector2 v = vec;
    v -= orig;
    dir -= orig;

    if(Core::angle(dir, v) <= 0.03f) //0.0003 de margem de erro.
    {
        /* Verifica se estao no mesmo quadrante. */
        bool same_x_signal = false;
        if(dir[0] > 0 && v[0] > 0) same_x_signal = true;
        if(dir[0] < 0 && v[0] < 0) same_x_signal = true;
        if(dir[0] == 0 && v[0] == 0) same_x_signal = true;

        if(same_x_signal)
        {
            if(dir[1] > 0 && v[1] > 0) return true;
            if(dir[1] < 0 && v[1] < 0) return true;
            if(dir[1] == 0 && v[1] == 0) return true;
        }
    }
    return false;
}

