/*
% Copyright (C) 2003-2021 GraphicsMagick Group
% Copyright (C) 2002 ImageMagick Studio
% Copyright 1991-1999 E. I. du Pont de Nemours and Company
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%               M   M   OOO   N   N  IIIII  TTTTT   OOO   RRRR                %
%               MM MM  O   O  NN  N    I      T    O   O  R   R               %
%               M M M  O   O  N N N    I      T    O   O  RRRR                %
%               M   M  O   O  N  NN    I      T    O   O  R R                 %
%               M   M   OOO   N   N  IIIII    T     OOO   R  R                %
%                                                                             %
%                                                                             %
%                   GraphicsMagick Progress Monitor Methods                   %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                               December 1995                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/monitor.h"
#include "magick/semaphore.h"
#include "magick/utility.h"

/*
  Global declarations.
*/
static MonitorHandler
  monitor_handler = (MonitorHandler) NULL;

static SemaphoreInfo
  *monitor_semaphore = 0;

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   D e s t r o y M a g i c k M o n i t o r                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  DestroyMagickMonitor() destroys the monitor environment.
%
%  The format of the DestroyMagickMonitor() method is:
%
%      DestroyMagickMonitor(void)
%
%
*/
void
DestroyMagickMonitor(void)
{
  DestroySemaphoreInfo(&monitor_semaphore);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   I n i t i a l i z e M a g i c k M o n i t o r                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  InitializeMagickMonitor() initializes the module loader.
%
%  The format of the InitializeMagickMonitor() method is:
%
%      MagickPassFail InitializeMagickMonitor(void)
%
%
*/
MagickPassFail
InitializeMagickMonitor(void)
{
  assert(monitor_semaphore == (SemaphoreInfo *) NULL);
  monitor_semaphore=AllocateSemaphoreInfo();
  return MagickPass;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   M a g i c k M o n i t o r                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  MagickMonitor() calls the monitor handler method with a text string that
%  describes the task and a measure of completion.  The method returns True
%  on success otherwise False if an error is encountered, e.g. if there was a
%  user interrupt.
%
%  This function is deprecated.  Please use MagickMonitorFormatted() instead.
%
%  The format of the MagickMonitor method is:
%
%      MagickPassFail MagickMonitor(const char *text,
%        const magick_int64_t quantum,const magick_uint64_t span,
%        ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o text: Description of the task being performed.
%
%    o quantum: The position relative to the span parameter which represents
%      how much progress has been made toward completing a task.
%
%    o span: The span relative to completing a task.
%
%    o exception: Return any errors or warnings in this structure.
%
*/
MagickExport MagickPassFail
MagickMonitor(const char *text,
              const magick_int64_t quantum,
              const magick_uint64_t span,
              ExceptionInfo *exception)
{
  MagickPassFail
    status = MagickPass;

  assert(text != (const char *) NULL);
  ProcessPendingEvents(text);
  if (monitor_handler != (MonitorHandler) NULL)
    {
      LockSemaphoreInfo(monitor_semaphore);
      status=(*monitor_handler)(text,quantum,span,exception);
      UnlockSemaphoreInfo(monitor_semaphore);
    }
  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
+   M a g i c k M o n i t o r  A c t i v e                                    %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  MagickMonitorAtive() returns MagickTrue if a progress monitor callback
%  has been registered, or MagickFalse if no progress monitor is active.
%
%  The format of the MagickMonitorActive method is:
%
%      MagickBool MagickMonitor(void)
%
*/
MagickExport MagickBool
MagickMonitorActive(void)
{
  return monitor_handler != (MonitorHandler) NULL ? MagickTrue : MagickFalse;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   M a g i c k M o n i t o r F o r m a t t e d                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  MagickMonitorFormatted() calls the monitor handler method with a
%  printf type format specification and variable argument list.  Also
%  passed are quantum and span values which provide a measure of
%  completion.  The method returns MagickPass on success otherwise
%  MagickFail if an error is encountered, e.g. if there was a user
%  interrupt.  If MagickFail is returned, the calling code is expected
%  to terminate whatever is being monitored as soon as possible.
%
%  Most callers of this function will use the QuantumTick() macro to
%  decide when it should be called.  The QuantumTick() macro is designed
%  to deliver no more than 100 events in a span (representing 1-100%)
%  and to distribute events as evenly as possible over the span so that
%  events are reported for every 1% of progress when possible.
%
%  The format of the MagickMonitorFormatted method is:
%
%      MagickPassFail MagickMonitorFormatted(const magick_int64_t quantum,
%                       const magick_uint64_t span,ExceptionInfo *exception,
%                       const char *format,...)
%
%  A description of each parameter follows:
%
%    o quantum: The position relative to the span parameter which represents
%      how much progress has been made toward completing a task.
%
%    o span: The span relative to completing a task.
%
%    o exception: Return any errors or warnings in this structure.
%
%    o format:  A string describing the format to use to write the remaining
%      arguments.
%
*/
MagickExport MagickPassFail
MagickMonitorFormatted(const magick_int64_t quantum,
                       const magick_uint64_t span,
                       ExceptionInfo *exception,
                       const char *format,...)
{
  MagickPassFail
    status = MagickPass;

  if (monitor_handler != (MonitorHandler) NULL)
    {
      va_list
        operands;

      char
        text[MaxTextExtent];

      va_start(operands,format);
      FormatStringList(text,format,operands);
      va_end(operands);
      /*
        Serialize calls to the handler so that it will
        never be invoked by more than one thread at a time.

        When OpenMP is used, many different threads may invoke the
        handler, but the implementation of the handler might not be
        prepared for that.

        It is theoretically possible for events to be delivered out of
        order if the handler takes so much time to complete that
        another thread is already delivering an event.  If the OS does
        not provide any lock ordering sematics (first come, first
        served) then behavior is indeterminate.  FIXME: if the
        progress monitor is called by a thread while the lock is still
        held, maybe just cache the latest progress and deliver it once
        the monitor hander returns so the most recent progress is
        delivered. The current semaphore design does not provide "try
        lock" behavior.
      */
      LockSemaphoreInfo(monitor_semaphore);
      status=(*monitor_handler)(text,quantum,span,exception);
      UnlockSemaphoreInfo(monitor_semaphore);
    }
  return status;
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S e t M o n i t o r H a n d l e r                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  SetMonitorHandler() sets the monitor handler to the specified method
%  and returns the previous monitor handler.
%
%  The format of the SetMonitorHandler method is:
%
%      MonitorHandler SetMonitorHandler(MonitorHandler handler)
%
%  A description of each parameter follows:
%
%    o handler: Specifies a pointer to a method to handle monitors.
%
%
*/
MagickExport MonitorHandler
SetMonitorHandler(MonitorHandler handler)
{
  MonitorHandler
    previous_handler;

  previous_handler=monitor_handler;
  monitor_handler=handler;
  return(previous_handler);
}
