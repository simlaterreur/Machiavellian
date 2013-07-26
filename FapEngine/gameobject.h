/*
    Throwing stuff
    To be sorted and cleaned
    or even deleted entirely
*/


#if !defined(__GAMEOBJECT_H__)
#define __GAMEOBJECT_H__



class GameObject
{
public:
    void virtual Render() const; // is a game object something to be rendered by default?
    void virtual Tick();  // some sort of inner logic to be updated

protected:


};


class AnimatedObject : public GameObject
{
public:
    void virtual Animate();


protected:

};


#endif