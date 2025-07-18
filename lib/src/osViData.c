#include "libultra_internal.h"

OSViMode osViModePalLan1 = {
    /*type*/ 2,
    /*comRegs*/
    { /*ctrl*/ 12574,
      /*width*/ 320,
      /*burst*/ 65348153,
      /*vSync*/ 525,
      /*hSync*/ 3093,
      /*leap*/ 202705941,
      /*hStart*/ 7078636,
      /*xScale*/ 512,
      /*vCurrent*/ 0 },
    /*fldRegs*/
    { { /*origin*/ 640,
        /*yScale*/ 1024,
        /*vStart*/ 2425343,
        /*vBurst*/ 918020,
        /*vIntr*/ 2 },
      { /*origin*/ 640,
        /*yScale*/ 1024,
        /*vStart*/ 2425343,
        /*vBurst*/ 918020,
        /*vIntr*/ 2 } }
};

OSViMode osViModeMpalLan1 = {
    /*type*/ 16,
    /*comRegs*/
    { /*ctrl*/ 12574,
      /*width*/ 320,
      /*burst*/ 67380026,
      /*vSync*/ 625,
      /*hSync*/ 1379433,
      /*leap*/ 208604270,
      /*hStart*/ 8389376,
      /*xScale*/ 512,
      /*vCurrent*/ 0 },
    /*fldRegs*/
    { { /*origin*/ 640,
        /*yScale*/ 1024,
        /*vStart*/ 6226489,
        /*vBurst*/ 590443,
        /*vIntr*/ 2 },
      { /*origin*/ 640,
        /*yScale*/ 1024,
        /*vStart*/ 6226489,
        /*vBurst*/ 590443,
        /*vIntr*/ 2 } }
};
