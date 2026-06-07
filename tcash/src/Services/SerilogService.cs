using Serilog;
using Serilog.Core;
using Serilog.Events;
using Serilog.Formatting.Compact;

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

public class LoggingOptions
{
    public bool EnableConsole { get; set; }
    public bool EnableTextFile { get; set; }
    public bool EnableJsonFile { get; set; }

    public string LogDirectory { get; set; } = "logs";
}

public static class SerilogService
{
    private static LoggingLevelSwitch LevelSwitch =
        new LoggingLevelSwitch(LogEventLevel.Information);

    public static void Init(int levelFromConfig, string environment, LoggingOptions options)
    {
        LevelSwitch.MinimumLevel =
            LogLevelMapper.ToSerilog((LogLevel)levelFromConfig);

        var loggerConfig = new LoggerConfiguration()

            .MinimumLevel.ControlledBy(LevelSwitch)

            .MinimumLevel.Override("Microsoft", LogEventLevel.Warning)
            .MinimumLevel.Override("System", LogEventLevel.Warning)

            .Enrich.WithProperty("Application", "tcash")
            .Enrich.WithProperty("Environment", environment)
            .Enrich.FromLogContext();

        // -------------------------
        // OPTIONAL: CONSOLE
        // -------------------------
        if (options.EnableConsole)
        {
            loggerConfig = loggerConfig.WriteTo.Console();
        }

        // -------------------------
        // OPTIONAL: HUMAN READABLE FILE
        // -------------------------
        if (options.EnableTextFile)
        {
            loggerConfig = loggerConfig.WriteTo.File(
                path: "logs/app-.log",
                rollingInterval: RollingInterval.Day,
                rollOnFileSizeLimit: true,
                retainedFileCountLimit: 14
            );
        }

        // -------------------------
        // OPTIONAL: JSON FILE
        // -------------------------
        if (options.EnableJsonFile)
        {
            loggerConfig = loggerConfig.WriteTo.File(
                formatter: new CompactJsonFormatter(),
                path: "logs/structured-.log",
                rollingInterval: RollingInterval.Day
            );
        }

        Log.Logger = loggerConfig.CreateLogger();
    }
}
