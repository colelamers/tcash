namespace tcash.Models;

// Entity Framework assumes the Model name is the table name
public class AuditLog
{
    public int Id { get; set; }
    public string Action { get; set; } = "";
    public string User { get; set; } = "";
    public DateTime Timestamp { get; set; }
}
