import java.util.*;
import java.io.*;

public enum ObjectMapperFactory
{
    INSTANCE;
    public static <T> T readValue(ObjectMapper objectMapper, String value, class<T> outputClass)
    {
        return objectMapper.readValue(value, outputClass);
    }

    public ObjectMapper objectMapper()
    {
        // Does something
    }
}