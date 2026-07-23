using System;
using System.IO;
using System.IO.Compression;

public static class UnzipCompat {
  public static int Main(string[] args) {
    try {
      if (args.Length >= 2 && args[0] == "-Z1") {
        using (var z = ZipFile.OpenRead(args[1]))
          foreach (var e in z.Entries) Console.WriteLine(e.FullName);
        return 0;
      }
      if (args.Length >= 3 && args[0] == "-p") {
        using (var z = ZipFile.OpenRead(args[1])) {
          var e = z.GetEntry(args[2].Replace('\\', '/'));
          if (e == null) return 11;
          using (var s = e.Open())
          using (var o = Console.OpenStandardOutput()) s.CopyTo(o);
        }
        return 0;
      }
      return 2;
    } catch (Exception ex) {
      Console.Error.WriteLine(ex.Message);
      return 1;
    }
  }
}
