using Xunit;
using System.Text.Json;

public class JsonConfigurationTests
{
    private string CreateTempConfigDir()
    {
        var path = Path.Combine(Path.GetTempPath(), Guid.NewGuid().ToString());

        Directory.CreateDirectory(path);

        return path;
    }

    private void WriteConfig(string dir, string name, string json)
    {
        var file = Path.Combine(dir, $"{name}.json");
        File.WriteAllText(file, json);
    }

    // ----------------------------
    // TEST 1: Load + Get raw file
    // ----------------------------
    [Fact]
    public void Get_ShouldReturnJsonElement_WhenFileExists()
    {
        var dir = CreateTempConfigDir();

        WriteConfig(dir, "app", "{ \"name\": \"tcash\" }");

        var config = new JsonConfiguration(dir);

        var result = config.Get("app");

        Assert.True(result.TryGetProperty("name", out var value));
        Assert.Equal("tcash", value.GetString());
    }

    // ----------------------------
    // TEST 2: Missing file throws
    // ----------------------------
    [Fact]
    public void Get_ShouldThrow_WhenFileMissing()
    {
        var dir = CreateTempConfigDir();

        var config = new JsonConfiguration(dir);

        Assert.Throws<KeyNotFoundException>(() =>
        {
            config.Get("missing");
        });
    }

    // ----------------------------
    // TEST 3: Strongly typed deserialization
    // ----------------------------
    private class TestConfig
    {
        public string Name { get; set; } = "";
    }

    [Fact]
    public void GetT_ShouldDeserializeCorrectly()
    {
        var dir = CreateTempConfigDir();

        WriteConfig(dir, "app", "{ \"Name\": \"tcash\" }");

        var config = new JsonConfiguration(dir);

        var result = config.Get<TestConfig>("app");

        Assert.Equal("tcash", result.Name);
    }

    // ----------------------------
    // TEST 4: GetSection works
    // ----------------------------
    [Fact]
    public void GetSection_ShouldReturnNestedProperty()
    {
        var dir = CreateTempConfigDir();

        WriteConfig(dir, "app", "{ \"logging\": { \"level\": \"debug\" } }");

        var config = new JsonConfiguration(dir);

        var section = config.GetSection("app", "logging");

        Assert.True(section.TryGetProperty("level", out var level));
        Assert.Equal("debug", level.GetString());
    }

    // ----------------------------
    // TEST 5: Reload updates cache
    // ----------------------------
    [Fact]
    public void Reload_ShouldUpdateCache_WhenFileChanges()
    {
        var dir = CreateTempConfigDir();

        WriteConfig(dir, "app", "{ \"value\": 1 }");

        var config = new JsonConfiguration(dir);

        var before = config.Get("app");

        WriteConfig(dir, "app", "{ \"value\": 2 }");

        config.Reload();

        var after = config.Get("app");

        Assert.NotEqual(before.GetRawText(), after.GetRawText());
    }
}
