#include "Piano.h"

int main()
{
    //TODO : Setup static linking to hopefully
    //       make everything into the exe so we don't dlls anymore
    //                - look into statically linking the .wav base file as well
    //        - create an option to let the user change pitch via gui
    //        - create an option to let the user change the volume via gui
    //        - pick better gui color, maybe add some sort of shading?
    //        - ability to change base sound layer so it works more like a synth
    //        - look into hissing / static problem maybe figure something out
    //        - make gui redraw properly when resizing
    Piano piano;
    piano.update();
    return 0;
}