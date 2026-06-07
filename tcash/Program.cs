using System;
using System.IO;
using System.Linq;
using tcash;
using tcash.Models;
using tcash.Services;
using Microsoft.EntityFrameworkCore;

var dbPath = Path.Combine(
    AppContext.BaseDirectory,
    "data",
    "app.db"
);

var dir = Path.GetDirectoryName(dbPath);

if (dir != null && !Directory.Exists(dir))
{
    Directory.CreateDirectory(dir);
}

//
// -------------------------
// 1. EF CORE LAYER
// -------------------------
//
using (var db = new AuditLogDbContext(dbPath))
{
    db.Database.EnsureCreated();
    if (!db.AuditLogs.Any())
    {
        for (int i = 1; i <= 10; i++)
        {
            db.AuditLogs.Add(new AuditLog
            {
                Action = $"Action_{i}",
                User = $"User_{i % 3}",
                Timestamp = DateTime.UtcNow.AddMinutes(-i)
            });
        }

        db.SaveChanges();
    }

    var logs = db.AuditLogs
        .OrderBy(x => x.Id)
        .ToList();

    foreach (var log in logs)
    {
        Console.WriteLine($"{log.Id} | {log.Action} | {log.User} | {log.Timestamp}");
    }
}

//
// -------------------------
// 2. RAW SQL LAYER
// -------------------------
//
var sql = new SqliteService(dbPath);

// Example: parameterized query
var result = sql.Query(
    "SELECT * FROM AuditLogs WHERE User = @user",
    new Dictionary<string, object>
    {
        { "user", "User_1" }
    }
);

Console.WriteLine("\n--- RAW SQL RESULT ---");

foreach (var row in result)
{
    Console.WriteLine(string.Join(" | ", row));
}

//
// -------------------------
// 3. INTROSPECTION EXAMPLE
// -------------------------
//
var exists = sql.TableExists("AuditLogs");

Console.WriteLine($"\nTable exists: {exists}");

var schema = sql.GetTableSchema("AuditLogs");

Console.WriteLine("\n--- SCHEMA ---");

foreach (var col in schema)
{
    Console.WriteLine($"{col.Column} : {col.Type}");
}
