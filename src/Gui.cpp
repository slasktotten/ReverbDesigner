//
//  Gui.cpp
//  delay
//
//  Created by gustaf svenungsson on 05/03/2017.
//
//

#include "Gui.hpp"

Gui::Gui(Reverb& _patch, InputManager& _patch4, OutputManager& _patch5)
{
    reverb = &_patch;
    inputManager = &_patch4;
    outputManager = &_patch5;
    drawObject.clear();
    deleteState = false;
    patchFrom = nullptr;
    patchTo = nullptr;
}

//===============================================================================//

Gui::~Gui(){
    for(auto& obj : cables) delete obj;
    delete reverb;
    delete patchFrom;
    delete patchTo;
    delete pStart;
    pStart = nullptr;
    delete pEnd;
    pEnd = nullptr;
}

//===============================================================================//

void Gui::setup(string name)
{
    // add listeners for mouse events
    ofAddListener(ofEvents().mousePressed,  this, &Gui::mPressed);
    ofAddListener(ofEvents().mouseDragged,  this, &Gui::mDragged);
    ofAddListener(ofEvents().mouseReleased, this, &Gui::mReleased);
    
    setGUI(name);
    
    
    // colors
    combFilterIdle.r = 250;
    combFilterIdle.g = 50;
    combFilterIdle.b = 150;
    
    combFilterHighlight.r = 153;
    combFilterHighlight.g = 153;
    combFilterHighlight.b = 153;
    
    allPassIdle.r = 150;
    allPassIdle.g = 250;
    allPassIdle.b = 70;
    
    allPassHighlight.r = 153;
    allPassHighlight.g = 153;
    allPassHighlight.b = 153;
    
    audioSourceHiglight.r = 50;
    audioSourceHiglight.g = 60;
    audioSourceHiglight.g = 227;
    
    audioSourceIdle.r = 50;
    audioSourceIdle.g = 60;
    audioSourceIdle.g = 127;
    
}

//===============================================================================//

void Gui::update(int x, int y)
{
    for (auto el : drawObject) el->collision(x,y);
}

//===============================================================================//

void Gui::mPressed(ofMouseEventArgs &args){
    int x = args.x;
    int y = args.y;
    
    auto isAnyElementFalse = [](const DrawObject* obj){return obj->overBox;};
    
    result = any_of(drawObject.begin(), drawObject.end(), isAnyElementFalse);
    
    if(result)
    {
        
        if(!deleteState){
            createObject(x, y);
        } else {
            deleteObject(x,y);
        }
        
    } else {
        resetPatching("nothing selected, patching reset");
    }
}

//===============================================================================//

void Gui::mReleased(ofMouseEventArgs &args)
{
    int x = args.x;
    int y = args.y;
    for (auto& el : drawObject) el->mReleased(x,y);
}

//===============================================================================//

void Gui::mDragged(ofMouseEventArgs &args)
{
    int x = args.x;
    int y = args.y;
    //resetPatching("Mouse Dragged");
    for (auto& el : drawObject) el->mDragged(x, y);
}

//===============================================================================//


void Gui::addAllPass()
{
    deleteState = false;
    auto temp = dynamic_cast<Reverb*>(reverb);
    temp->addAllPassFilter(1);
    drawObject.push_back(new DrawObject(*temp->filters.back(), allPassHighlight, allPassIdle));
    temp = nullptr;
    setNewParameterGroup(*reverb->filters.back(), "All-Pass Filter");
    resetPatching("nothing selected, patching reset");
}

//===============================================================================//


void Gui::addComb()
{
    deleteState = false;
    auto temp = dynamic_cast<Reverb*>(reverb);
    temp->addCombFilter(1); // so we are running add filter of reverb
    drawObject.push_back(new DrawObject(*temp->filters.back(), combFilterHighlight, combFilterIdle)); // create a new draObject
    temp = nullptr;
    setNewParameterGroup(*reverb->filters.back(), "Comb Filter");
    resetPatching("nothing selected, patching reset");
}

//===============================================================================//

void Gui::addAudioSourceObject()
{
    deleteState = false;
    auto temp = dynamic_cast<InputManager*>(inputManager);
    temp->addAudioSourceObject();
    drawObject.push_back(new DrawObject(*inputManager->sources.back(), audioSourceHiglight, audioSourceIdle));
    temp = nullptr;
    setNewParameterGroup(*inputManager->sources.back(), "Input");
    resetPatching("nothing selected, patching reset");
}

//===============================================================================//

void Gui::addFinalOutput(){
    deleteState = false;
    auto temp = dynamic_cast<OutputManager*>(outputManager);
    temp->addNewOutputObject();
    drawObject.push_back(new DrawObject(*outputManager->outputs.back(), 0, 0));
    temp = nullptr;
    setNewParameterGroup(*outputManager->outputs.back(), "Output");
    resetPatching("nothing selected, patching reset");
}

//===============================================================================//


// iterate over our list of drawObjects to check if our cursor is over any of them
// if we haven't set patchFrom, grab the pointer to the patchClass being held by the drawObject
// otherwise we check if the object we're currently over is the same as patchFrom (if it is, don't patch, because patching an object to itself doesn't make sense, and we also check if patchFrom is set

void Gui::createObject(int x, int y){
    
    list<DrawObject*>::iterator it;
    
    for (it = drawObject.begin(); it != drawObject.end(); it++)
    {
        if((*it)->overBox)
        {
            (*it)->mPressed(x,y);
            
            if(patchFrom == nullptr){
                
                patchFrom = (*it)->getMyPtr(); // get the pointer being held by the drawObj
                
                objFrom = (*it); // we grab a pointer to the drawObj for the patchCables
                
                pStart = &(*it)->getMyPos;
                
                string parameterName = typeid(*patchFrom).name(); // get the name for the para
                
                setNewParameterGroup(*patchFrom, parameterName);
                
                cout << "patchFrom has ran" << endl;
                
            }  else if(patchFrom != (*it)->getMyPtr() && patchFrom != nullptr){
                
                patchTo = (*it)->getMyPtr();
                
                objTo = (*it);
                
                pEnd = &(*it)->getMyPos;
                
                // create a new patchCable
                cables.push_back(new PatchCable(*pStart, *pEnd, *objFrom, *objTo));
                
                patchTo->patch(*patchFrom, *patchTo);
                
                patchFrom->addConnection(*cables.back(), *patchTo);
                
                patchTo->addConnection(*cables.back(), *patchFrom);
                
                resetPatching("patch method has run");
                
            }
        }
    }
}

//===============================================================================//

void Gui::deleteObject(int x, int y){
    
    list<DrawObject*>::iterator it;
    
    for ( it = drawObject.begin(); it != drawObject.end(); ){
        // if we are currently over a drawObj
        if( (*it)->overBox){
            
            list<PatchCable*>::iterator cableIt;
            
            for ( cableIt = cables.begin(); cableIt != cables.end(); ){
                // start the unpatch method to delete all the references in appropriate order
                if( (*cableIt)->unpatch(*(*it))){ // unpatch takes a reference, so we need to dereference the iterator completely, hence **
                    
                    delete *cableIt; // delete the pointer the iterator is looking at
                    
                    *cableIt = nullptr; // set to null
                    
                    cableIt=cables.erase(cableIt); // delete the iterator from our patchCable list
                    
                } else{
                    
                    cableIt++;
                    
                }
                
            }
            
            delete * it;
            
            it = drawObject.erase(it);
            
        }
        
        else {
            
            ++it;
            
        }
        
    }
    
    deleteState = false;
    
}

//===============================================================================//

void Gui::draw()
{
    gui.draw();
    for (const auto& el : cables) el->display();
    for (const auto& el : drawObject) el->display();
}

//===============================================================================//

// method to check wheter we are currently over any object
bool Gui::anyElementFalse(DrawObject& _drawObject){
    if (_drawObject.overBox) return true;
    return false;
}

//===============================================================================//

void Gui::toggleDeletState(){
    deleteState = !deleteState;
}


//===============================================================================//

void Gui::resetPatching(string returnMsg){
    pEnd = nullptr;
    pStart = nullptr;
    patchTo   = nullptr;
    patchFrom = nullptr;
    objFrom = nullptr;
    objTo = nullptr;
    cout << returnMsg + " - Pointers Reset" << endl;
}

//===============================================================================//

void Gui::setGUI(string name){
    // reset the gui
    resetParameters();
    
    // give the gui a name
    gui.setup(name);
    
    // give the parametergroup a name
  //  parametergroup.setName(name);
    
    // create listeners for the gui buttons
    createCombFilter.addListener(this, &Gui::addComb);
    createAllPassFilter.addListener(this, &Gui::addAllPass);
    createAudioSource.addListener(this, &Gui::addAudioSourceObject);
    createFinalOutput.addListener(this, &Gui::addFinalOutput);
    deleteAnObject.addListener(this, &Gui::toggleDeletState);
    
    // add elements to gui
    gui.add(createCombFilter.setup("Create Comb Filter"));
    gui.add(createAllPassFilter.setup("Create All-Pass Filter"));
    gui.add(createAudioSource.setup("Create Audio Source"));
    gui.add(createFinalOutput.setup("Create Final Output"));
    gui.add(deleteAnObject.setup("Delete Object"));
    gui.add(parametergroup);
}

//===============================================================================//

// everytime we click on a a draw object we want to reset all the parameters
void Gui::resetParameters(){
    parametergroup.clear();
    gui.clear();
    createCombFilter.removeListener(this, &Gui::addComb);
    createAllPassFilter.removeListener(this, &Gui::addAllPass);
    createAudioSource.removeListener(this, &Gui::addAudioSourceObject);
    createFinalOutput.removeListener(this, &Gui::addFinalOutput);
    deleteAnObject.removeListener(this, &Gui::toggleDeletState);
    dblPara.clear();
    intPara.clear();
    floatPara.clear();
    cout << "parameter group cleared" << endl;
}

//===============================================================================//

void Gui::setNewParameterGroup( PatchClass& patch, string guiName){
    resetParameters();
    cout << "set new parametergroup" << endl;
    
    // type check to see what type of parameters we want to add
    // its not too expensive and we're only doing it "the once" every so often
    
    for(const auto& parameter : patch.parameters){
        if(auto temp = dynamic_cast<templateClass<int> *>(parameter)) {
            string name = temp->getName();
            intPara.emplace_back(new ofParameter<int>());
            parametergroup.add(intPara.back()->set(name, *temp->currentVal, temp->minVal, temp->maxVal));
            temp->setListener(intPara.back()->get());
            std::cout << "int type" << std::endl;
        }
        else if(auto temp = dynamic_cast<templateClass<float> *>(parameter)) {
            string name = temp->getName();
            floatPara.emplace_back(new ofParameter<float>());
            parametergroup.add(floatPara.back()->set(name,*temp->currentVal, temp->minVal, temp->maxVal));
            temp->setListener(floatPara.back()->get());
            std::cout << "float type" << std::endl;
        }
        else
            if(auto temp = dynamic_cast<templateClass<double> *>(parameter)) {
            string name = temp->getName();
            dblPara.emplace_back(new ofParameter<double>());
            parametergroup.add(dblPara.back()->set(name,*temp->currentVal, temp->minVal, temp->maxVal));
                temp->setListener(dblPara.back()->get());
                cout << "currentVal adress: " << temp->currentVal << endl;
        }
    }

    // give the gui a name
    gui.setup("Parameters");
    
    // give the parametergroup a name
    parametergroup.setName(guiName);
    
    // add elements to gui
    gui.add(createCombFilter.setup("Create Comb Filter"));
    gui.add(createAllPassFilter.setup("Create All-Pass Filter"));
    gui.add(createAudioSource.setup("Create Audio Source"));
    gui.add(createFinalOutput.setup("Create Final Output"));
    gui.add(deleteAnObject.setup("Delete Object"));
    gui.add(parametergroup);
    
    // create listeners for the gui buttons
    createCombFilter.addListener(this, &Gui::addComb);
    createAllPassFilter.addListener(this, &Gui::addAllPass);
    createAudioSource.addListener(this, &Gui::addAudioSourceObject);
    createFinalOutput.addListener(this, &Gui::addFinalOutput);
    deleteAnObject.addListener(this, &Gui::toggleDeletState);
    
}
