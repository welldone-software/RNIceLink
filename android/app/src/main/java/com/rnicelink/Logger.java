package com.rnicelink;

import android.util.Log;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

public final class Logger {
  private static final Map<String, Logger> loggers = new HashMap<>();

  public static Logger get(final String name) {
    synchronized (loggers) {
      Logger logger = loggers.get(name);
      if (logger == null) {
        logger = new Logger(name);
        loggers.put(name, logger);
      }

      return logger;
    }
  }

  private String name;

  public Logger(String name) {
    this.name = name;
  }

  public void verbose(String message, Object... args) {
    writeLog(name, Log.VERBOSE, message, args);
  }

  public void info(String message, Object... args) {
    writeLog(name, Log.INFO, message, args);
  }

  public void warning(Throwable e) {
    writeLogWithStackTrace(name, Log.WARN, getExceptionMessage(e), e);
  }

  public void warning(String message, Object... args) {
    writeLog(name, Log.WARN, message, args);
  }

  public void error(Throwable e) {
    writeLogWithStackTrace(name, Log.ERROR, getExceptionMessage(e), e);
  }

  public void error(String message, Object... args) {
    writeLog(name, Log.ERROR, message, args);
  }

  public void critical(Throwable e) {
    writeLogWithStackTrace(name, Log.ASSERT, getExceptionMessage(e), e);
  }

  public void critical(String message, Object... args) {
    writeLog(name, Log.ASSERT, message, args);
  }

  private void writeLog(String tag, int priority, String message, Object... args) {
    if (!Log.isLoggable(tag, priority)) {
      return;
    }
    Log.println(priority, tag, String.format(Locale.US, message, args));
  }

  private void writeLogWithStackTrace(String tag, int priority, String message, Throwable e) {
    if (!Log.isLoggable(name, priority)) {
      return;
    }
    Log.println(priority, name, message + '\n' + Log.getStackTraceString(e));
  }

  private String getExceptionMessage(Throwable e) {
    Throwable next = e;
    while (next.getMessage() == null && next.getCause() != null) {
      next = next.getCause();
    }

    if (next.getMessage() == null) {
      return next.getClass().getName();
    }

    return next.getMessage();
  }
}
