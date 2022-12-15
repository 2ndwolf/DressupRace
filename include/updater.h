#define _MTR_UPDATER_h_
#ifndef _MTR_UPDATER_h_

#include <vector>
#include <string>

#include "window.h"
#include "image.h"
#include "layer.h"
#include "spriteGroup.h"
#include "superGroup.h"
#include "text.h"

#include "primitives.h"

// MTR::UPD::LAY()

namespace MTR{

  namespace UPD{

    class Updater{
      protected:
      bool isOwner = false;
    };

    class LAY : public Updater{
      RND::Layer layer;

      inline LAY(RND::Layer player):
        layer(player)
        {};

      inline ~LAY(){
        layer.update(layer);
      };

    };

    class IMG : public Updater{
      RND::Image* image;

      inline IMG(RND::Image* pimage):
      image(pimage)
      {
        isOwner = image->addToQueue();
      };

      inline ~IMG(){
        if(isOwner) image->update(image);
      };
    };

    class SuPG : public Updater{
      RND::SuperGroup* superGroup;

      inline SuPG(RND::SuperGroup* psuperGroup):
      superGroup(psuperGroup)
      {
        isOwner = superGroup->addToQueue();
      };

      inline ~SuPG(){
        if(isOwner) superGroup->update(superGroup);
      };
    };

    class SG : public Updater{
      RND::SpriteGroup* spriteGroup;

      inline SG(RND::SpriteGroup* pspriteGroup):
      spriteGroup(pspriteGroup)
      {
        isOwner = spriteGroup->addToQueue();
      };

      inline ~SG(){
        if(isOwner) spriteGroup->update(spriteGroup);
      };
    };

    class TXT : public Updater{
      RND::Text* text;

      inline TXT(RND::Text* ptext):
      text(ptext)
      {
        isOwner = text->addToQueue();
      };

      inline ~TXT(){
        if(isOwner) text->update(text);
      };
    };
  }
}


#endif