#include "Caption.h"

std::string Caption::get_caption()
{
	return text;
}

void Caption::set_caption(std::string new_text)
{
	text = new_text;
}
