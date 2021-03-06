// edragon -- A file share application.
//
//! @file gtk_debug_ostream_operators.cc
//! @brief This file contains the implementation of ostream inserter operators used for debugging.
//
// Copyright (C) 2004, by
//
// Carlo Wood, Run on IRC <carlo@alinoe.com>
// RSA-1024 0x624ACAD5 1997-01-26                    Sign & Encrypt
// Fingerprint16 = 32 EC A7 B6 AC DB 65 A6  F6 F6 55 DD 1C DC FF 61
//
// This file may be distributed under the terms of the Q Public License
// version 1.0 as appearing in the file LICENSE.QPL included in the
// packaging of this file.

#include "sys.h"

#ifdef DEBUG
#include <iostream>
#include "casereturnstr.h"
#include "debug.h"
#include "gtk_debug_ostream_operators.h"

namespace debug {

/*!
 * @internal
 * @brief Return a string literal representing the name of the \c GdkEventType \a event_type.
 */
char const* GdkEventType_name(GdkEventType event_type)
{
  switch(event_type)
  {
    // See enum GdkEventType in gtk+-2.2.4/gdk/gdkevents.h
    CASERETURNSTR(GDK_NOTHING);
    CASERETURNSTR(GDK_DELETE);
    CASERETURNSTR(GDK_DESTROY);
    CASERETURNSTR(GDK_EXPOSE);
    CASERETURNSTR(GDK_MOTION_NOTIFY);
    CASERETURNSTR(GDK_BUTTON_PRESS);
    CASERETURNSTR(GDK_2BUTTON_PRESS);
    CASERETURNSTR(GDK_3BUTTON_PRESS);
    CASERETURNSTR(GDK_BUTTON_RELEASE);
    CASERETURNSTR(GDK_KEY_PRESS);
    CASERETURNSTR(GDK_KEY_RELEASE);
    CASERETURNSTR(GDK_ENTER_NOTIFY);
    CASERETURNSTR(GDK_LEAVE_NOTIFY);
    CASERETURNSTR(GDK_FOCUS_CHANGE);
    CASERETURNSTR(GDK_CONFIGURE);
    CASERETURNSTR(GDK_MAP);
    CASERETURNSTR(GDK_UNMAP);
    CASERETURNSTR(GDK_PROPERTY_NOTIFY);
    CASERETURNSTR(GDK_SELECTION_CLEAR);
    CASERETURNSTR(GDK_SELECTION_REQUEST);
    CASERETURNSTR(GDK_SELECTION_NOTIFY);
    CASERETURNSTR(GDK_PROXIMITY_IN);
    CASERETURNSTR(GDK_PROXIMITY_OUT);
    CASERETURNSTR(GDK_DRAG_ENTER);
    CASERETURNSTR(GDK_DRAG_LEAVE);
    CASERETURNSTR(GDK_DRAG_MOTION);
    CASERETURNSTR(GDK_DRAG_STATUS);
    CASERETURNSTR(GDK_DROP_START);
    CASERETURNSTR(GDK_DROP_FINISHED);
    CASERETURNSTR(GDK_CLIENT_EVENT);
    CASERETURNSTR(GDK_VISIBILITY_NOTIFY);
    CASERETURNSTR(GDK_NO_EXPOSE);
    CASERETURNSTR(GDK_SCROLL);
    CASERETURNSTR(GDK_WINDOW_STATE);
    CASERETURNSTR(GDK_SETTING);
    CASERETURNSTR(GDK_OWNER_CHANGE);
    CASERETURNSTR(GDK_GRAB_BROKEN);
  }
  DoutFatal(dc::fatal, "Unhandled GdkEventType in GdkEventType_name");
}

/*!
 * @internal
 * @brief Return a string literal representing the name of the \c GdkModifierType \a modifier_type.
 */
char const* GdkModifierType_name(GdkModifierType modifier_type)
{
  switch(modifier_type)
  {
    // See enum GdkModifierType in gtk+-2.2.4/gdk/gdktypes.h
    CASERETURNSTR(GDK_SHIFT_MASK);
    CASERETURNSTR(GDK_LOCK_MASK);
    CASERETURNSTR(GDK_CONTROL_MASK);
    CASERETURNSTR(GDK_MOD1_MASK);
    CASERETURNSTR(GDK_MOD2_MASK);
    CASERETURNSTR(GDK_MOD3_MASK);
    CASERETURNSTR(GDK_MOD4_MASK);
    CASERETURNSTR(GDK_MOD5_MASK);
    CASERETURNSTR(GDK_BUTTON1_MASK);
    CASERETURNSTR(GDK_BUTTON2_MASK);
    CASERETURNSTR(GDK_BUTTON3_MASK);
    CASERETURNSTR(GDK_BUTTON4_MASK);
    CASERETURNSTR(GDK_BUTTON5_MASK);
    CASERETURNSTR(GDK_RELEASE_MASK);
    default:	// This should never have been an enum in the first place, these are (mask) bits.
      break;
  }
  DoutFatal(dc::fatal, "Unhandled GdkModifierType in GdkModifierType_name");
}

/*!
 * @internal
 * @brief Print \c GdkModifierType bits \a mask to ostream \a os.
 */
void print_GdkModifierType_mask_on(std::ostream& os, gint mask)
{
  if (mask == 0)
  {
    os << '0';
    return;
  }
  bool first = true;
  for (guint m = 1; m; m <<= 1)
    if ((m & GDK_MODIFIER_MASK) && (m & mask))
    {
      if (!first)
        os << '|';
      else
	first = false;
      os << GdkModifierType_name((GdkModifierType)m);
    }
}

} // namespace debug

using namespace debug;

//! Debug inserter for <tt>GdkEventType</tt>.
std::ostream& operator<<(std::ostream& os, GdkEventType event_type)
{
  return os << GdkEventType_name(event_type);
}

//! Debug inserter for <tt>GdkEvent const*</tt>.
std::ostream& operator<<(std::ostream& os, GdkEvent const* event)
{
  return os << "{ " << event->type << " ((GdkEvent*)" << (void*)event << ") }";
}

//! Debug inserter for <tt>GtkWidget const*</tt>.
std::ostream& operator<<(std::ostream& os, GtkWidget const* widget)
{
  os << "{ ";
  if (widget->name)
    os << '"' << widget->name << '"';
  else
    os << "*no name*";
  return os << " ((GtkWidget*)" << (void*)widget << ") }";
}

//! Debug inserter for <tt>GtkAllocation const*</tt>.
std::ostream& operator<<(std::ostream& os, GtkAllocation const* al)
{
  return os << "{ (x:" << al->x << ", y:" << al->y << ", width:" << al->width << ", height:" << al->height << ") }";
}

std::ostream& operator<<(std::ostream& os, GdkWindow const* window)
{
  return os << "{ ((GdkWindow*)" << (void*)window << ") }";
}

std::ostream& operator<<(std::ostream& os, GdkDevice const* device)
{
  os << "{ ";
  if (device->name)
    os << '"' << device->name << '"';
  else
    os << "*no name*";
  return os << " ((GdkDevice*)" << (void*)device << ") }";
}

std::ostream& operator<<(std::ostream& os, GdkModifierType modifier_type)
{
  return os << GdkModifierType_name(modifier_type);
}

std::ostream& operator<<(std::ostream& os, GdkEventButton const* eb)
{
  os << "{ (" << eb->type << ", " << eb->window << ", send_event:" << (bool)eb->send_event << ", time:" << eb->time <<
      ", x:" << eb->x << ", y:" << eb->y << ", axes:" << eb->axes << ", state:";
  print_GdkModifierType_mask_on(os, eb->state);
  return os << ", button:" << eb->button << ", " << eb->device <<
      ", x_root:" << eb->x_root << ", y_root:" << eb->y_root << ") }";
}

std::ostream& operator<<(std::ostream& os, GdkEventMotion const* em)
{
  os << "{ (" << em->type << ", " << em->window << ", send_event:" << (bool)em->send_event << ", time:" << em->time <<
      ", x:" << em->x << ", y:" << em->y << ", axes:" << em->axes << ", state:";
  print_GdkModifierType_mask_on(os, em->state);
  return os << ", is_hint:" << (bool)em->is_hint << ", " << em->device <<
      ", x_root:" << em->x_root << ", y_root:" << em->y_root << ") }";  
}

std::ostream& operator<<(std::ostream& os, GdkEventConfigure const* ec)
{
  return os << "{ (" << ec->type << ", " << ec->window << ", send_event: " << (bool)ec->send_event <<
      ", x:" << ec->x << ", y:" << ec->y << ", width:" << ec->width << ", height:" << ec->height << ") }";
}

std::ostream& operator<<(std::ostream& os, GdkRectangle const& rect)
{
  return os << "(x:" << rect.x << ", y:" << rect.y << ", width:" << rect.width << ", height:" << rect.height << ")";
}

std::ostream& operator<<(std::ostream& os, GdkSegment const& segment)
{
  return os << "(x1:" << segment.x1 << ", y1:" << segment.y1 << ", x2:" << segment.x2 << ", y2:" << segment.y2 << ")";
}

std::ostream& operator<<(std::ostream& os, GdkSegment const* segment)
{
  return os << "{ " << *segment << " }";
}

// From gdk/gdkregion-generic.h
typedef GdkSegment GdkRegionBox;
struct _GdkRegion
{
  long size;
  long numRects;
  GdkRegionBox* rects;
  GdkRegionBox extents;
};

std::ostream& operator<<(std::ostream& os, GdkRegion const* region)
{
  os << "{ (size:" << region->size << ", numRects:" << region->numRects << ", rects:{";
  for (int i = 0; i < region->numRects; i++)
  {
    GdkRegionBox rect;
    rect = region->rects[i];
    if (i != 0)
      os << ", ";
    os << rect;
  }
  os << "}, extents:" << region->extents << ") }";
  return os;
}

std::ostream& operator<<(std::ostream& os, GdkEventExpose const* ee)
{
  return os << "{ (" << ee->type << ", " << ee->window << ", send_event:" << (bool)ee->send_event <<
      ", area:" << ee->area << ", region:" << ee->region << ", count: " << ee->count << ") }";
}

std::ostream& operator<<(std::ostream& os, GtkAction const* action)
{
  return os << "{ (" << gtk_action_get_name((GtkAction*)action) << ") }";
}
#endif // DEBUG

