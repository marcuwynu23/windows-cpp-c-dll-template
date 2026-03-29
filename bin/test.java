import java.lang.foreign.Arena;
import java.lang.foreign.FunctionDescriptor;
import java.lang.foreign.Linker;
import java.lang.foreign.MemorySegment;
import java.lang.foreign.SymbolLookup;
import java.lang.foreign.ValueLayout;
import java.lang.invoke.MethodHandle;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

/**
 * Loads lib.dll via the JDK Foreign Function &amp; Memory API (FFM). Requires JDK 22+.
 * <p>On JDK 24+, run with {@code --enable-native-access=ALL-UNNAMED} to avoid native-access
 * warnings (see bin/README.md).
 */
public class test {
    public static void main(String[] args) throws Throwable {
        Path dll = resolveDll();
        Linker linker = Linker.nativeLinker();
        try (Arena arena = Arena.ofConfined()) {
            SymbolLookup lookup = SymbolLookup.libraryLookup(dll, arena);

            MemorySegment helloAddr = lookup.find("hello").orElseThrow();
            MethodHandle hello = linker.downcallHandle(helloAddr, FunctionDescriptor.ofVoid());

            MemorySegment printAddr = lookup.find("printNumber").orElseThrow();
            MethodHandle printNumber =
                    linker.downcallHandle(printAddr, FunctionDescriptor.ofVoid(ValueLayout.JAVA_INT));

            hello.invokeExact();
            printNumber.invokeExact(23);
        }
    }

    private static Path resolveDll() throws URISyntaxException {
        var loc = test.class.getProtectionDomain().getCodeSource();
        if (loc != null) {
            Path base = Paths.get(loc.getLocation().toURI());
            if (Files.isRegularFile(base)) {
                base = base.getParent();
            }
            if (base != null) {
                return base.resolve("lib.dll").toAbsolutePath().normalize();
            }
        }
        return Paths.get("lib.dll").toAbsolutePath().normalize();
    }
}
