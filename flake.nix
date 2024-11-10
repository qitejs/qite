{
  description = "Qite: A JavaScript execution engine";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-stable";

  outputs = { self, nixpkgs }: {
    packages.x86_64-linux.default = with nixpkgs.legacyPackages.x86_64-linux; stdenv.mkDerivation {
      pname = "qite";  # Name of the package
      version = "1.0"; # Version of the package

      src = ./.; # Use the current directory as the source

      buildInputs = [ cmake ]; # Specify build inputs (CMake in this case)

      # Define the build phases
      buildPhase = ''
        mkdir -p build
        cd build
        cmake ..
        make
      '';

      # Define the install phase if you want to install the binary
      installPhase = ''
        mkdir -p $out/bin
        cp build/qite $out/bin/ # Adjust if the executable has a different name
      '';

      # Define a meta section for additional information
      meta = {
        description = "A JavaScript execution engine.";
        license = licenses.gpl3; # Specify the GPL-3.0 license
      };
    };
  };
}
