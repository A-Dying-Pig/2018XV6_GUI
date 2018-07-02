#include "types.h"
#include "x86.h"
#include "defs.h"
#include "kbd.h"
#include "APObject.h"

extern void sendMessage(int wndId,AMessage *msg);
extern AWndList wndList;

void kbdInterupt()
{
	static int shift = 0;
	static uchar *charcode[2] = {
		normalMap, e0Map
	};

	uint st, data;

	st = inb(KBSTATP);
	data = inb(KBDATAP);

	//cprintf("state : %d\n", st);
	//cprintf("data  : %d\n", data);
	if ((st & KBS_DIB) == 0 || (st & 0x20) != 0)
	{
		//cprintf("kbdInterupt return : %d\n", st);
		return;
	}

	if (data == 0xE0) {
		//cprintf("kbd error data 0xE0\n");
		shift = 1;
		return;
	}
	else if (data & 0x80) {
		//cprintf("test2");
		// Key released
        //cprintf("key released!\n");
		data &= 0x7F;
		AMessage msg;
		msg.type = MSG_KEY_UP;
		msg.param = charcode[shift][data];
		if (shift)
			shift = 0;

        //cprintf("sending message!\n");
		sendMessage(wndList.head, &msg);
        //cprintf("kdb message sent!\n");
		return;
	}
	AMessage msg;
	msg.type = MSG_KEY_DOWN;
	msg.param = charcode[shift][data];
	//cprintf("msg.param send:%d\n",msg.param);
	if (shift)
		shift = 0;
    //cprintf("sending message!\n");
	sendMessage(wndList.head, &msg);
    //cprintf("kdb message sent!\n");

}

int
kbdgetc(void)
{
  static uint shift;
  static uchar *charcode[4] = {
    normalmap, shiftmap, ctlmap, ctlmap
  };
  uint st, data, c;

  st = inb(KBSTATP);
  data = inb(KBDATAP);

  if((st & KBS_DIB) == 0 || (st & 0x20) != 0)
    return -1;

  if (st & 0xc0)
  {
    return -1;
  }
    
  if(data == 0xE0){
    shift |= E0ESC;
    return 0;
  } else if(data & 0x80){
    // Key released
    data = (shift & E0ESC ? data : data & 0x7F);
    shift &= ~(shiftcode[data] | E0ESC);
    return 0;
  } else if(shift & E0ESC){
    // Last character was an E0 escape; or with 0x80
    data |= 0x80;
    shift &= ~E0ESC;
  }

  shift |= shiftcode[data];
  shift ^= togglecode[data];
  c = charcode[shift & (CTL | SHIFT)][data];
  if(shift & CAPSLOCK){
    if('a' <= c && c <= 'z')
      c += 'A' - 'a';
    else if('A' <= c && c <= 'Z')
      c += 'a' - 'A';
  }
  
  return c;
}

void
kbdintr(void)
{
  //consoleintr(kbdgetc);
	kbdInterupt();
}
