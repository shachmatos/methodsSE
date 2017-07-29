﻿#include "UIComponent.h"

UIComponent::UIComponent(short x_pos, short y_pos, int w, int h, BorderType border, Color tColor, Color bColor, UIComponent *parent):
position{ x_pos, y_pos }, width(w), height(h), borderType(border),
textColor(tColor), backgroundColor(bColor), focus(false) {}

UIComponent & UIComponent::getRoot() {
	UIComponent *result = this;
	while (result->parent) {
		result = result->parent;
	}
	return *result;
}

void UIComponent::removeFromScreen() const {
	ConsoleController ctrl = CCTRL;
	//SetConsoleCursorPosition(h, position);
	ctrl.setPosition(position);
	//SetConsoleTextAttribute(h, 0);

	// FIXME: this assumes the UI is black -Yftah
	ctrl.setColors(0, 0);
	COORD c = { position.X, position.Y };
	for (short i = 0; i < height + 1; i++) {
		for (short j = 0; j < width + 2; j++) {
			std::cout << " ";
		}
		//SetConsoleCursorPosition(h, { c.X, ++c.Y });
		++c.Y;
		ctrl.setPosition(c);
	}
}

void UIComponent::draw() {

	drawBorder();
}

void UIComponent::setVisible(bool visible) {
	bool prev = this->is_visible;
	this->is_visible = visible;
	if (visible) {
		if (this->isInteractable() && !prev) {
			CCTRL.attachObserver(this);
		}
		draw();
	}
	else {
		if (this->isInteractable() && prev) {
			CCTRL.detachObserver(this);
		}
		removeFromScreen();
	}
}

void UIComponent::invertColors() {
	Color tmp = this->backgroundColor;
	this->backgroundColor = this->textColor;
	this->textColor = tmp;
}

void UIComponent::applyColors(bool fg, bool bg) {
	CCTRL.setColors(this->textColor, this->backgroundColor, fg, bg);
}

void UIComponent::drawBorder() const {
	// SetConsoleCursorPosition(h, position);
	ConsoleController ctrl = CCTRL;
	ctrl.setPosition(position);
	// SetConsoleTextAttribute(h, textColor | FOREGROUND_INTENSITY | backgroundColor * 16);
	ctrl.setColors(textColor, backgroundColor, focus);
	short i;
	COORD c;
	BorderCharacters bc;
	switch (borderType) {
	case Dotted:
		bc = { '\xDA', '\xBF', '\xC0', '\xD9', '-', '|' };
		break;
	case Solid:
		bc = { '\xDA', '\xBF', '\xC0','\xD9', '\xC4', '\xB3' };
		break;
	case Double:
		bc = { '\xC9', '\xBB', '\xC8','\xBC', '\xCD', '\xBA' };
		break;
	case None: return;
	default: return;
	}

	std::cout << bc.leftTopCorner;

	for (i = 0; i < width; i++)
		std::cout << bc.horizontal;

	std::cout << bc.rightTopCorner;

	for (i = 1; i < height; i++) {
		c = { position.X, position.Y + i };
		//SetConsoleCursorPosition(h, c);
		ctrl.setPosition(c);
		std::cout << bc.vertical;
		c = { position.X + width + 1, position.Y + i };
		//SetConsoleCursorPosition(h, c);
		ctrl.setPosition(c);
		std::cout << bc.vertical;
	}

	c = { position.X, position.Y + i };
	//SetConsoleCursorPosition(h, c);
	ctrl.setPosition(c);
	std::cout << bc.leftBottomCorner;
	for (i = 0; i < width; i++) {
		std::cout << bc.horizontal;
	}
	std::cout << bc.rightBottomCorner;
}




/*==========================*/


//#include "UIComponent.h"
//#include <iostream>
//
//UIComponent::UIComponent(short x_pos, short y_pos, short w, short h, BorderType border, Color tColor, Color bColor, UIComponent *parent) : Control::Control(x_pos, y_pos, w, h), parent(parent),
//	borderType(border),
//	textColor(tColor), backgroundColor(bColor) {
//}
//
//UIComponent & UIComponent::getRoot() {
//	UIComponent *result = this;
//	while (result->parent) {
//		result = result->parent;
//	}
//	return *result;
//}
//
//void UIComponent::removeFromScreen() const {
//	//ConsoleController ctrl = CCTRL;
//	//SetConsoleCursorPosition(h, position);
//
//	GFX.moveTo(left, top);
//	//ctrl.setPosition({ top, left });
//	//SetConsoleTextAttribute(h, 0);
//
//	// FIXME: this assumes the UI is black -Yftah
//	//ctrl.setColors(0, false, 0, false);
//	GFX.setForeground(Black);
//	GFX.setBackground(Black);
//	COORD c = { left, top };
//	for (short i = 0; i < height + 1; i++) {
//		for (short j = 0; j < width + 2; j++) {
//			std::cout << " ";
//		}
//		//SetConsoleCursorPosition(h, { c.X, ++c.Y });
//		++c.Y;
//		GFX.moveTo(c.X, c.Y);
//		//ctrl.setPosition(c);
//	}
//}
//
//void UIComponent::draw() {
//
//	drawBorder();
//}
//
//void UIComponent::drawBorder() const {
//	// SetConsoleCursorPosition(h, position);
//	//ConsoleController ctrl = CCTRL;
//	//ctrl.setPosition(position);
//	GFX.moveTo(left, top);
//	// SetConsoleTextAttribute(h, textColor | FOREGROUND_INTENSITY | backgroundColor * 16);
//	//ctrl.setColors(textColor, true, backgroundColor, false);
//	GFX.setBackground(backgroundColor);
//	GFX.setForeground(textColor);
//	short i;
//	COORD c;
//	BorderCharacters bc;
//	switch (borderType) {
//	case Dotted:
//		bc = { '\xDA', '\xBF', '\xC0', '\xD9', '-', '|' };
//		break;
//	case Solid:
//		bc = { '\xDA', '\xBF', '\xC0','\xD9', '\xC4', '\xB3' };
//		break;
//	case Double:
//		bc = { '\xC9', '\xBB', '\xC8','\xBC', '\xCD', '\xBA' };
//		break;
//	case None: return;
//	default: return;
//	}
//
//	printf("%c", bc.leftTopCorner);
//
//	for (i = 0; i < width; i++)
//		printf("%c", bc.horizontal);
//
//	printf("%c", bc.rightTopCorner);
//
//	for (i = 1; i < height; i++) {
//		c = { left, top + i };
//		//SetConsoleCursorPosition(h, c);
//		//ctrl.setPosition(c);
//		GFX.moveTo(c.X, c.Y);
//		printf("%c", bc.vertical);
//		c = { left + width + 1, top + i };
//		//SetConsoleCursorPosition(h, c);
//		//ctrl.setPosition(c);
//		GFX.moveTo(c.X, c.Y);
//		printf("%c", bc.vertical);
//	}
//
//	c = { left, top + i };
//	//SetConsoleCursorPosition(h, c);
//	//ctrl.setPosition(c);
//	GFX.moveTo(c.X, c.Y);
//	printf("%c", bc.leftBottomCorner);
//	for (i = 0; i < width; i++) {
//		printf("%c", bc.horizontal);
//	}
//	printf("%c", bc.rightBottomCorner);
//}