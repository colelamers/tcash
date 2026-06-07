using Serilog;
using Serilog.Core;
using Serilog.Events;

namespace tcash.Services;
public enum LogLevel
{
    kVerbose = 0,
    kDebug = 1,
    kInformation = 2,
    kWarning = 3,
    kError = 4,
    kFatal = 5
}

public static class LogLevelMapper
{
    public static LogEventLevel ToSerilog(LogLevel level)
    {
        return level switch
        {
            LogLevel.kVerbose => LogEventLevel.Verbose,
            LogLevel.kDebug => LogEventLevel.Debug,
            LogLevel.kInformation => LogEventLevel.Information,
            LogLevel.kWarning => LogEventLevel.Warning,
            LogLevel.kError => LogEventLevel.Error,
            LogLevel.kFatal => LogEventLevel.Fatal,
            _ => LogEventLevel.Information
        };
    }
}

public static class SerilogSetup
{
    /// <summary>
    /// Basic log level setup only from config
    /// </summary>
    public static void Init(int levelFromConfig)
    {
        var switchLevel = new LoggingLevelSwitch(
            LogLevelMapper.ToSerilog((LogLevel)levelFromConfig)
        );

        Log.Logger = new LoggerConfiguration()
            .MinimumLevel.ControlledBy(switchLevel)
            .WriteTo.Console()
            .WriteTo.File("logs/app.log", rollingInterval: RollingInterval.Day)
            .CreateLogger();
    }
}
