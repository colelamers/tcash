using Microsoft.EntityFrameworkCore;
using tcash.Models;

namespace tcash.Services;

public class AuditLogDbContext : DbContext
{
    public DbSet<AuditLog> AuditLogs { get; set; }
    private readonly string db_path_;

    public AuditLogDbContext(string dbPath)
    {
        db_path_ = dbPath;
    }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseSqlite($"Data Source={db_path_}");
    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<AuditLog>()
            .HasKey(x => x.Id);
    }
}

/*
Example of retrieval with entity
using (var db = new AppDbContext(dbPath))
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
*/
