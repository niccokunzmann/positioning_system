    {
      static Samples instance; // Guaranteed to be destroyed.
                               // Instantiated on first use.
      return instance;
    }