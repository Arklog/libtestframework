#ifndef WINDOW_H
#define WINDOW_H

#include <cctype>
#include <ncurses.h>
#include <vector>

class Window {
private:
  WINDOW *_window;
  char _border;

  int _padx;
  int _pady;

public:
  Window(WINDOW *window);
  Window(WINDOW *window, char border, int padx, int pady);
  ~Window();

  /**
   * Return this window ncurses window pointer
   */
  WINDOW *get();

  /**
   * Reset cursor position
   */
  void reset_cursor();

  /**
   * Clear this window screen
   */
  void clear();

  /**
   * Draw this window border
   */
  void draw_border();

  /**
   * Set this window border character
   *
   * @param c		the new border character, must be printable
   */
  void set_border(char c);

  /**
   * Get this window border character
   *
   * @return		the character used to draw the border
   */
  char get_border();

  /**
   * Pure virtual function used to draw this window
   */
  virtual void display() = 0;

  /**
   * Refresh this window screen
   */
  void refresh();

  /**
   * Get this window x cursor position
   *
   * @return		the current position of this window
   * 				cursor in x
   */
  int get_x();

  /**
   * Set this window x cursor position
   *
   * @param x		the new x position of the cursor, it must
   * 				be inferior to the maximum x position
   */
  void set_x(int x);

  /**
   * Return this window y cursor position
   *
   * @return		the current position of this window
   * 				cursor in y
   */
  int get_y();

  /**
   * Set this window y cursor position
   *
   * @param y		the new y position of the cursor, it must be
   * 				inferior to the maximum y position
   */
  void set_y(int y);

  int get_maxx();
  int get_maxy();
};

#endif
