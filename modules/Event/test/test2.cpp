#include <iostream>
#include "axEvent.h"
#include "axEventManager.h"
#include "axMsg.h"
#include <vector>

int main()
{
    // Créer le event manager.
    ax::Event::Manager evt_manager;
    
    // Créer 4 objets.
    std::vector<ax::Event::Object*> objs(4);
    
    for(int i = 0; i < objs.size(); i++)
    {
        objs[i] = new ax::Event::Object(&evt_manager);
    }
    
    // Créer un lamda qui affiche un message.
    ax::Event::Function potato = [](ax::Event::Msg* msg)
    {
        std::cout << "Potato obj " <<
            ax::Event::SimpleMsg<int>::Cast(msg).GetMsg() << std::endl;
    };
    
    // Connecte le lamda à l'objet 0 et 2.
    objs[0]->AddEventFunction("Potato", potato);
    objs[2]->AddEventFunction("Potato", potato);
    
    
    // Ensuite je parcours tous les objets et si la
    // fonction Patato exist dans l'objet, je call la fonction.
    for(int i = 0; i < objs.size(); i++)
    {
        // Façon très douteuse d'appeler la fonction.
        try
        {
            ax::Event::SimpleMsg<int> msg(i);
            objs[i]->GetEventFunction("Potato")(&msg);
        }
        catch(std::exception e)
        {
            std::cerr << e.what() << std::endl;
        }
        
        
        // Façon legit d'appeler la fonction.
        ax::Event::Function fct = objs[i]->GetEventFunction("Potato");
        
        if(fct)
        {
            ax::Event::SimpleMsg<int> msg(i);
            fct(&msg);
        }
    }
    
    std::cout << std::endl;
    
    //-----------------------------------------------------------------------
    // En haut de cette ligne on ne s'est pas encore servie du event manager.
    
    
    
    // Là, je connect la fonction Potato de l'objet 0 et je l'ajoute à l'id 2010.
    // L'id 2010 aurait pu être n'importe quoi.
    objs[0]->AddConnection(2010, objs[0]->GetEventFunction("Potato"));
    
    // L'event manager, c'est un std::map de paire de ax::Event::ID avec un std::multimap
    // de paire d'id et de fonction.
    //
    // std::map<ax::Event::ID, std::multimap<ax::Event::Id, ax::Event::Function>>
    //
    // C'est la même chose que cela :
    //
    //           ID de l'objet                  fct id               la fonction callback
    // --------------------------------------------------------------------------------------------
    // std::map< unsigned int,  std::multimap<unsigned int,  std::function<void(ax::Event::Msg*)>>>
    //
    // Dans le fond c'est un map de multimap. Pour chaque object on a plusieurs connection à
    // plusieurs id.
    
    
    // Ici je connecte une fonction comme je le ferais normalement
    // (sans le map local à l'objet ex : Potato).
    // Ceci ajoute les connections dans l'event manager.
    objs[0]->AddConnection(2010, ax::Event::Function([](ax::Event::Msg* msg)
    {
        std::cout << "Not potato obj 0 : msg -> " <<
            ax::Event::SimpleMsg<int>::Cast(msg).GetMsg() << std::endl;
    }));

    
    // Ensuite j'envoi l'event dans l'event queue du event manager.
    // Si il y a deux fonction de connecté à un id cela ajoute deux fonctions à la queue.
    objs[0]->PushEvent(2010, new ax::Event::SimpleMsg<int>(8927));
    
    
    // Et je call le deux prochaines fonctions de la queue du event manager.
    evt_manager.CallNext();
    evt_manager.CallNext();

    
    std::cout << std::endl;

    // Ensuite delete tous les objets.
    for(auto& n : objs)
    {
        delete n;
    }
    
    objs.clear();
    
    
    return 0;
}

