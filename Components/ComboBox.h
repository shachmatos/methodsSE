#pragma once
#include "UIComponent.h"
#include <vector>
#include <string>
using namespace std;

class ComboBox : public UIComponent {

	ComboBox* _originalState;
	vector<string> options;
	int selected_index;
	int temp_index;
	bool open_down;
	bool open;

	// Copy CTOR
	ComboBox(ComboBox* o);


public:
	ComboBox(string* options, int len, short pos_x, short pos_y, short width, BorderType border = Double, Color tColor = White, Color bColor = Black, UIComponent* parent = NULL);
	void draw();

	// General UI Methods
	bool canGetFocus() { return true; }
	void mouseClicked(MOUSE_EVENT_RECORD);
	void keyPressed(KEY_EVENT_RECORD);

	// ComboBox Specific
	void toggle();
	string getValue() const;
	

	~ComboBox();
};

