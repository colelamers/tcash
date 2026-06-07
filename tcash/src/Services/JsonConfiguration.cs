using System.Text.Json;

public class JsonConfiguration
{
    private readonly string config_path_;
    private readonly Dictionary<string, JsonElement> cache_ = 
        new Dictionary<string, JsonElement>();

    public JsonConfiguration(string configDirectory)
    {
        config_path_ = configDirectory;

        if (!Directory.Exists(config_path_))
        {
            throw new DirectoryNotFoundException($"Config folder not found: {config_path_}");
        }

        LoadAllConfigs();
    }

    private void LoadAllConfigs()
    {
        foreach (var file in Directory.GetFiles(config_path_, "*.json"))
        {
            using (var doc = JsonDocument.Parse(File.ReadAllText(file)))
            {
                var root = doc.RootElement.Clone();
                var key = Path.GetFileNameWithoutExtension(file);
                cache_[key] = root;
            }
        }
    }

    public JsonElement Get(string fileName)
    {
        if (cache_.TryGetValue(fileName, out var value))
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
        cache_.Clear();
        LoadAllConfigs();
    }
}
