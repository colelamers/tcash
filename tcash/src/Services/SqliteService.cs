using Microsoft.Data.Sqlite;

public class SqliteService
{
    private readonly string db_path_;
    private readonly string connection_string_;

    public SqliteService(string dbPath)
    {
        db_path_ = dbPath;
        var dir = Path.GetDirectoryName(db_path_);

        if (dir != null && !Directory.Exists(dir))
        {
            Directory.CreateDirectory(dir);
        }

        connection_string_ = $"Data Source={db_path_}";

        if (!File.Exists(db_path_))
        {
            File.Create(db_path_).Dispose();
        }
    }

    // -------------------------
    // INTERNAL CONNECTION
    // -------------------------
    private SqliteConnection open_connection()
    {
        var connection = new SqliteConnection(connection_string_);
        connection.Open();

        return connection;
    }

    // -------------------------
    // PARAMETER HELPERS
    // -------------------------
    private void apply_parameters(SqliteCommand command, Dictionary<string, object>? parameters)
    {
        if (parameters == null)
        {
            return;
        }

        foreach (var pair in parameters)
        {
            command.Parameters.AddWithValue("@" + pair.Key, pair.Value);
        }
    }

    // -------------------------
    // EXECUTE (no results)
    // -------------------------
    public void Execute(string sql, Dictionary<string, object>? parameters = null)
    {
        using (var connection = open_connection())
        using (var command = connection.CreateCommand())
        {
            command.CommandText = sql;
            apply_parameters(command, parameters);
            command.ExecuteNonQuery();
        }
    }

    // -------------------------
    // QUERY → List<List<object>>
    // -------------------------
    public List<List<object>> Query(string sql, Dictionary<string, object>? parameters = null)
    {
        var results = new List<List<object>>();

        using (var connection = open_connection())
        using (var command = connection.CreateCommand())
        {
            command.CommandText = sql;

            apply_parameters(command, parameters);

            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    var row = new List<object>();

                    for (int i = 0; i < reader.FieldCount; i++)
                    {
                        row.Add(reader.GetValue(i));
                    }

                    results.Add(row);
                }
            }
        }

        return results;
    }

    // -------------------------
    // QUERY → Dictionary rows
    // -------------------------
    public List<Dictionary<string, object>> QueryNamed(string sql, Dictionary<string, object>? parameters = null)
    {
        var results = new List<Dictionary<string, object>>();

        using (var connection = open_connection())
        using (var command = connection.CreateCommand())
        {
            command.CommandText = sql;

            apply_parameters(command, parameters);

            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    var row = new Dictionary<string, object>();

                    for (int i = 0; i < reader.FieldCount; i++)
                    {
                        row[reader.GetName(i)] = reader.GetValue(i);
                    }

                    results.Add(row);
                }
            }
        }

        return results;
    }

    // -------------------------
    // EXECUTE SQL FILE
    // -------------------------
    public void ExecuteFile(string filePath)
    {
        if (!File.Exists(filePath))
        {
            throw new FileNotFoundException($"SQL file not found: {filePath}");
        }

        var sql = File.ReadAllText(filePath);

        Execute(sql);
    }

    // -------------------------
    // TABLE EXISTS
    // -------------------------
    public bool TableExists(string tableName)
    {
        var sql = @"
            SELECT name 
            FROM sqlite_master 
            WHERE type='table' AND name = @name;
        ";

        using (var connection = open_connection())
        using (var command = connection.CreateCommand())
        {
            command.CommandText = sql;
            command.Parameters.AddWithValue("@name", tableName);

            using (var reader = command.ExecuteReader())
            {
                return reader.Read();
            }
        }
    }

    // -------------------------
    // DATABASE EXISTS
    // -------------------------
    public bool DatabaseExists()
    {
        return File.Exists(db_path_);
    }

    // -------------------------
    // TABLE SCHEMA INFO
    // -------------------------
    public class Schema {
        public string Column { get; set; }
        public string Type { get; set; }
        public Schema (string col, string art) {
            this.Column = col;
            this.Type = art;
        }
    }
    public List<Schema> GetTableSchema(string tableName)
    {
        var results = new List<Schema>();

        using (var connection = open_connection())
        using (var command = connection.CreateCommand())
        {
            command.CommandText = $"PRAGMA table_info({tableName});";

            using (var reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    var column = reader.GetString(1);
                    var type = reader.GetString(2);

                    results.Add(new Schema(column, type));
                }
            }
        }

        return results;
    }
}
