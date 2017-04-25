//
//  TemplatedParameter.h
//  delay
//
//  Created by gustaf svenungsson on 21/03/2017.
//
//

#ifndef TemplatedParameter_h
#define TemplatedParameter_h


/*
 we need a small dynamic object to handle the parameters
 because they will be different in each derived class of the patchClass, I opted for a templated class
 we need to have it inherit from a regular class so that we can utilize polymorphism (otherwise we would have to create one vector for each type of templatedClass *
 */
class templateInterface{
    protected :
    
    string name;
    
    virtual ~templateInterface() {
    }
    
public:
    std::string getName(){
        return name;
    }
    
};

template <typename T>
class templateClass : public templateInterface{
private:
    
    const T* listener;
    
    const T** parameter; // using ptr-to-ptr because we need to manipulate the adress of another pointer
    
    void setCurrentVal(const T *&t){
        currentVal = t;
    }
    
    void setParameter(const T *&t){
        *parameter = t;
    }


    
public:
    templateClass(const T& current, const T& min, const T& max, const string& _name, const T *&_theParameter) :
    currentVal(&current), // why is this a warning?
    minVal(min),
    maxVal(max),
    parameter(&_theParameter)
    {
        name = _name;
    }
    
    const T* currentVal;
    
    T minVal;
    
    T maxVal;
    
    void setListener(const T& t){
        
        listener   = &t; // set the listener to listen. in our case this is an ofParameter
        
        setCurrentVal(listener); // set the currentVal from our startingVal to the parameter
        
        setParameter(currentVal); // set the parameter from our patchClass to currentVal
        }
    

};


#endif /* TemplatedParameter_h */
