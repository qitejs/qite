{
  description = "Qite: A JavaScript execution engine";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/release-22.11"; # Use a valid branch or tag

  outputs = { self, nixpkgs }: let
    # Function to build the package for a given platform
    buildPackage = platform: let
      inherit (nixpkgs.legacyPackages.${platform}) stdenv cmake;
      # Directly reference the license you want to use
      license = nixpkgs.legacyPackages.${platform}.licenses.gpl3; # Specify the GPL-3.0 license
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
        cp build/qite $out/bin/ # Adjust if the executable has a different name
      '';

      # Define a meta section for additional information
      meta = {
        description = "A JavaScript execution engine.";
        license = license; # Use the license defined above
      };
    };
  in {
    # Define packages for different platforms
    packages.x86_64-linux.default = buildPackage "x86_64-linux";
    packages.x86_64-darwin.default = buildPackage "x86_64-darwin";
    packages.x86_64-windows.default = buildPackage "x86_64-windows";
  };
}
