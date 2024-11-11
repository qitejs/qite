{
  description = "Qite: A JavaScript execution engine";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/release-22.11"; # Use a valid branch or tag

  outputs = { self, nixpkgs }: let
    # Function to build the package for a given platform
    buildPackage = platform: let
      inherit (nixpkgs.legacyPackages.${platform}) stdenv cmake;

      # Define the custom license
      customLicense = {
        # Define the license attributes
        name = "The Qite License";
      };

    in
    stdenv.mkDerivation {
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
        cp build/qite $out/bin/
      '';

      # Define a meta section for additional information
      meta = {
        description = "A JavaScript execution engine.";
        license = customLicense; # Use the custom license defined above
      };
    };
  in {
    # Define packages for different platforms
    packages.x86_64-linux.default = buildPackage "x86_64-linux";
    packages.x86_64-darwin.default = buildPackage "x86_64-darwin";
    packages.x86_64-windows.default = buildPackage "x86_64-windows";
  };
}
