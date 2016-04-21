// updated 2/14/2016

#include "event_manager.h"
#include "gpl_assert.h"
#include "statement_block.h"
using namespace std;

/* static */ Event_manager *Event_manager::m_instance = 0;

/* static */ Event_manager * Event_manager::instance()
{
  if (!m_instance){
    m_instance = new Event_manager();
  }
  return m_instance;
}

Event_manager::Event_manager()
{
}

Event_manager::~Event_manager()
{
}

void Event_manager::add_handler(Window::Keystroke keystroke, Statement_block* block){
	handlers[keystroke].push_back(block);
}

void 
Event_manager::execute_handlers(Window::Keystroke keystroke)
{
	for(unsigned int i=0; i< handlers[keystroke].size(); ++i){
		handlers[keystroke][i]->execute();
	}
}
