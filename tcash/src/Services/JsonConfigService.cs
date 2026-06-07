using System.Text.Json;
namespace tcash.Services;

public class JsonConfigService
{
    private readonly string ConfigPath;
    private readonly Dictionary<string, JsonElement> Cache =
        new Dictionary<string, JsonElement>();

    public JsonConfigService(string configDirectory)
    {
        ConfigPath = configDirectory;

        if (!Directory.Exists(ConfigPath))
        {
            throw new DirectoryNotFoundException($"Config folder not found: {ConfigPath}");
        }

        LoadAllConfigs();
    }

    private void LoadAllConfigs()
    {
        foreach (var file in Directory.GetFiles(ConfigPath, "*.json"))
        {
            using (var doc = JsonDocument.Parse(File.ReadAllText(file)))
            {
                var root = doc.RootElement.Clone();
                var key = Path.GetFileNameWithoutExtension(file);
                Cache[key] = root;
            }
        }
    }

    public JsonElement Get(string fileName)
    {
        if (Cache.TryGetValue(fileName, out var value))
        {
            return value;
        }

        throw new KeyNotFoundException($"Config '{fileName}' not found");
    }

    public T Get<T>(string fileName)
    {
        var element = Get(fileName);
        var result = JsonSerializer.Deserialize<T>(element.GetRawText());

        if (result == null)
        {
            throw new Exception($"Failed to deserialize config: {fileName}");
        }

        return result;
    }

    public JsonElement GetSection(string fileName, string section)
    {
        var root = Get(fileName);

        if (root.TryGetProperty(section, out var sectionValue))
        {
            return sectionValue;
        }

        throw new KeyNotFoundException($"Section '{section}' not found in '{fileName}'");
    }

    public void Reload()
    {
        Cache.Clear();
        LoadAllConfigs();
    }
}
