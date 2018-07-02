#include "types.h"
#include "x86.h"
#include "defs.h"
#include "traps.h"
#include "memlayout.h"
#include "APHandle.h"
#include "APObject.h"

extern void sendMessage(int wndId,AMessage *msg);
extern AWndList wndList;

void InitHandle()
{
	outb(0x64,0x8a);
	outb(0x64,0xd4);
	outb(0x60,0xf4);
	outb(0x64,0x60);
	outb(0x60,0x47);
	for (int i = 0; i < BtnNum; i++)
	{
		my_btn[i].state = Null;
		my_btn[i].time = 0;
	}

	picenable(IRQ_HANDLE);
	ioapicenable(IRQ_HANDLE, 0);
}

void HandleInterupt()
{
	uint state, data;

	state = inb(HANDLESTAP);	
	//cprintf("state : %d\n", state);
	
	/*if ((state & 0x01) == 0 || (state & 0x20) != 0)
	{
		cprintf("HandleInterupt return : %d\n", state);
		return;
	}*/
	//data = inb(HANDLEATAP);
	cprintf("data  : %d\n", data);
	AMessage msg;
	msg.type = MSG_HANDLE_DOWN;
	msg.param = 1;
	sendMessage(wndList.head,&msg);
	switch (data)
	{
		

	}


}

void DealHandleMessage(int ticks)
{
	for (int i = 0; i < BtnNum; i++)
	{
		if (my_btn[i].state != Null)
		{

		}
	}
}
